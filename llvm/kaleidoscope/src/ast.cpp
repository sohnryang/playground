#include <ast.h>

#include <cstdint>
#include <stdexcept>

#include <llvm/IR/BasicBlock.h>
#include <llvm/IR/Constants.h>
#include <llvm/IR/Function.h>
#include <llvm/IR/Type.h>
#include <llvm/IR/Verifier.h>

template <typename T>
LiteralExprNode<T>::LiteralExprNode(T value) : value(value) {}

template <>
llvm::Value *LiteralExprNode<int>::codegen(
    std::shared_ptr<llvm::LLVMContext> context,
    std::shared_ptr<llvm::Module> module,
    std::shared_ptr<llvm::IRBuilder<>> builder,
    std::map<std::string, llvm::Value *> &named_values) {
  return llvm::ConstantInt::get(
      *context, llvm::APInt(32, static_cast<uint64_t>(value), true));
}

template <>
llvm::Value *LiteralExprNode<double>::codegen(
    std::shared_ptr<llvm::LLVMContext> context,
    std::shared_ptr<llvm::Module> module,
    std::shared_ptr<llvm::IRBuilder<>> builder,
    std::map<std::string, llvm::Value *> &named_values) {
  return llvm::ConstantFP::get(*context, llvm::APFloat(value));
}

VariableExprNode::VariableExprNode(const std::string &name) : name(name) {}

llvm::Value *
VariableExprNode::codegen(std::shared_ptr<llvm::LLVMContext> context,
                          std::shared_ptr<llvm::Module> module,
                          std::shared_ptr<llvm::IRBuilder<>> builder,
                          std::map<std::string, llvm::Value *> &named_values) {
  auto *val = named_values[name];
  if (val == nullptr)
    throw std::logic_error("unknown variable name");
  return val;
}

BinaryExprNode::BinaryExprNode(std::string op, std::unique_ptr<ExprNode> lhs,
                               std::unique_ptr<ExprNode> rhs)
    : op(op), lhs(std::move(lhs)), rhs(std::move(rhs)) {}

llvm::Value *
BinaryExprNode::codegen(std::shared_ptr<llvm::LLVMContext> context,
                        std::shared_ptr<llvm::Module> module,
                        std::shared_ptr<llvm::IRBuilder<>> builder,
                        std::map<std::string, llvm::Value *> &named_values) {
  auto lhs_val = lhs->codegen(context, module, builder, named_values),
       rhs_val = rhs->codegen(context, module, builder, named_values);
  if (lhs_val == nullptr || rhs_val == nullptr)
    return nullptr;

  if (op == "+")
    return builder->CreateAdd(lhs_val, rhs_val);
  else if (op == "-")
    return builder->CreateSub(lhs_val, rhs_val);
  else if (op == "*")
    return builder->CreateMul(lhs_val, rhs_val);
  else if (op == "<") {
    // TODO: support int compare
    lhs_val = builder->CreateFCmpULT(lhs_val, rhs_val);
    return builder->CreateUIToFP(lhs_val, llvm::Type::getDoubleTy(*context));
  } else
    throw std::logic_error("invalid binary operator");
}

CallExprNode::CallExprNode(const std::string &callee,
                           std::vector<std::unique_ptr<ExprNode>> args)
    : callee(callee), args(std::move(args)) {}

llvm::Value *
CallExprNode::codegen(std::shared_ptr<llvm::LLVMContext> context,
                      std::shared_ptr<llvm::Module> module,
                      std::shared_ptr<llvm::IRBuilder<>> builder,
                      std::map<std::string, llvm::Value *> &named_values) {
  llvm::Function *callee_func = module->getFunction(callee);
  if (callee_func == nullptr)
    throw std::logic_error("unknown function");

  if (callee_func->arg_size() != args.size())
    throw std::logic_error("argument count mismatch");

  std::vector<llvm::Value *> argv;
  for (auto &arg : args) {
    argv.push_back(arg->codegen(context, module, builder, named_values));
    if (argv.back() == nullptr)
      throw std::logic_error("codegen failed for arg");
  }
  return builder->CreateCall(callee_func, argv);
}

PrototypeNode::PrototypeNode(
    const std::string &name,
    std::vector<std::pair<std::string, std::string>> args,
    std::string return_type)
    : name(name), args(std::move(args)), return_type(return_type) {}
const std::string &PrototypeNode::get_name() const { return name; }

llvm::Function *
PrototypeNode::codegen(std::shared_ptr<llvm::LLVMContext> context,
                       std::shared_ptr<llvm::Module> module) {
  std::vector<llvm::Type *> func_arg_types;
  for (auto &arg : args) {
    if (arg.second == "int")
      func_arg_types.push_back(llvm::Type::getInt32Ty(*context));
    else if (arg.second == "float")
      func_arg_types.push_back(llvm::Type::getDoubleTy(*context));
    else
      throw std::logic_error("unknown arg type");
  }
  llvm::Type *func_return_type;
  if (return_type == "int")
    func_return_type = llvm::Type::getInt32Ty(*context);
  else if (return_type == "float")
    func_return_type = llvm::Type::getDoubleTy(*context);
  else if (return_type == "void")
    func_return_type = llvm::Type::getVoidTy(*context);
  else
    throw std::logic_error("unknown return type");
  auto func_type =
      llvm::FunctionType::get(func_return_type, func_arg_types, false);
  auto func = llvm::Function::Create(func_type, llvm::Function::ExternalLinkage,
                                     name, module.get());
  auto it = args.begin();
  for (auto &arg : func->args())
    arg.setName((it++)->first);
  return func;
}

FunctionNode::FunctionNode(std::unique_ptr<PrototypeNode> proto,
                           std::unique_ptr<ExprNode> func_body)
    : proto(std::move(proto)), func_body(std::move(func_body)) {}

llvm::Function *
FunctionNode::codegen(std::shared_ptr<llvm::LLVMContext> context,
                      std::shared_ptr<llvm::Module> module,
                      std::shared_ptr<llvm::IRBuilder<>> builder,
                      std::map<std::string, llvm::Value *> &named_values) {
  auto func = module->getFunction(proto->get_name());
  if (func == nullptr)
    func = proto->codegen(context, module);
  if (func == nullptr)
    return nullptr;

  auto block = llvm::BasicBlock::Create(*context, "entry", func);
  builder->SetInsertPoint(block);

  named_values.clear();
  for (auto &arg : func->args())
    named_values[std::string(arg.getName())] = &arg;

  auto ret = func_body->codegen(context, module, builder, named_values);
  if (ret == nullptr) {
    func->eraseFromParent();
    return nullptr;
  }
  builder->CreateRet(ret);
  llvm::verifyFunction(*func);
  return func;
}

template class LiteralExprNode<int>;
template class LiteralExprNode<double>;
