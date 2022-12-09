#include <irgen.h>
#include <typechecker.h>

#include <cstdint>
#include <fstream>
#include <stdexcept>

#include <llvm/IR/BasicBlock.h>
#include <llvm/IR/Constant.h>
#include <llvm/IR/Type.h>
#include <llvm/IR/Verifier.h>
#include <llvm/Support/raw_os_ostream.h>

#include <fmt/core.h>

IRGen::IRGen()
    : globals(), context(new llvm::LLVMContext()),
      module(new llvm::Module("Kaleidoscope", *context)),
      builder(new llvm::IRBuilder<>(*context)) {}

void IRGen::codegen(std::string const &filename,
                    std::vector<StatementNode> &ast) {
  std::ofstream outfile(filename);
  llvm::raw_os_ostream outstream(outfile);
  for (auto &subtree_root : ast)
    std::visit(*this, subtree_root);
  module->print(outstream, nullptr);
}

void IRGen::operator()(FunctionNode &node) {
  if (functions.count(node.proto.name))
    throw std::logic_error(
        fmt::format("function named {} already exists", node.proto.name));
  std::vector<llvm::Type *> arg_types_llvm;
  std::map<std::string, Type> arg_vars;
  std::vector<Type> arg_types;
  for (auto &arg : node.proto.args) {
    if (arg.second == "int") {
      arg_types_llvm.push_back(llvm::Type::getInt32Ty(*context));
      arg_vars[arg.first] = Type::kInt;
      arg_types.push_back(Type::kInt);
    } else if (arg.second == "float") {
      arg_types_llvm.push_back(llvm::Type::getDoubleTy(*context));
      arg_vars[arg.first] = Type::kFloat;
      arg_types.push_back(Type::kFloat);
    } else
      throw std::logic_error(fmt::format("unknown arg type: {}", arg.second));
  }
  llvm::Type *return_type_llvm;
  Type return_type;
  if (node.proto.return_type == "int") {
    return_type = Type::kInt;
    return_type_llvm = llvm::Type::getInt32Ty(*context);
  } else if (node.proto.return_type == "float") {
    return_type = Type::kFloat;
    return_type_llvm = llvm::Type::getDoubleTy(*context);
  } else if (node.proto.return_type == "void") {
    return_type = Type::kVoid;
    return_type_llvm = llvm::Type::getVoidTy(*context);
  } else
    throw std::logic_error(
        fmt::format("unknown return type: {}", node.proto.return_type));
  functions[node.proto.name] = std::make_pair(return_type, arg_types);
  auto func_type =
      llvm::FunctionType::get(return_type_llvm, arg_types_llvm, false);
  auto func = llvm::Function::Create(func_type, llvm::Function::ExternalLinkage,
                                     node.proto.name, module.get());
  auto it = node.proto.args.begin();
  for (auto &arg : func->args())
    arg.setName((it++)->first);
  if (!node.func_body.has_value())
    return;
  auto block = llvm::BasicBlock::Create(*context, "entry", func);
  builder->SetInsertPoint(block);

  for (auto &arg : arg_vars)
    globals[arg.first] = arg.second;
  for (auto &arg : func->args())
    global_symbols[std::string(arg.getName())] = &arg;
  auto ret = std::visit(*this, node.func_body.value());
  for (auto &arg : arg_vars)
    globals.erase(arg.first);
  for (auto &arg : func->args())
    global_symbols.erase(std::string(arg.getName()));
  if (return_type == Type::kInt)
    builder->CreateRet(builder->CreateFPToSI(ret, builder->getInt32Ty()));
  else if (return_type == Type::kFloat)
    builder->CreateRet(builder->CreateSIToFP(ret, builder->getDoubleTy()));
  llvm::verifyFunction(*func);
}

llvm::Value *IRGen::operator()(LiteralExprNode<int> &node) {
  return llvm::ConstantInt::get(
      *context, llvm::APInt(32, static_cast<uint64_t>(node.value), true));
}

llvm::Value *IRGen::operator()(LiteralExprNode<double> &node) {
  return llvm::ConstantFP::get(*context, llvm::APFloat(node.value));
}

llvm::Value *IRGen::operator()(VariableExprNode &node) {
  return global_symbols.at(node.name);
}

llvm::Value *IRGen::operator()(std::unique_ptr<BinaryExprNode> &node) {
  auto lhs_val = std::visit(*this, node->lhs),
       rhs_val = std::visit(*this, node->rhs);
  if (lhs_val == nullptr || rhs_val == nullptr)
    throw std::logic_error("failed to codegen lhs or rhs");

  ExprTypeChecker checker(globals, functions);
  auto lhs_type = std::visit(checker, node->lhs),
       rhs_type = std::visit(checker, node->rhs);
  if (node->op == "+") {
    if (lhs_type == Type::kInt && rhs_type == Type::kInt)
      return builder->CreateAdd(lhs_val, rhs_val);
    return builder->CreateFAdd(
        builder->CreateSIToFP(lhs_val, builder->getDoubleTy()),
        builder->CreateSIToFP(rhs_val, builder->getDoubleTy()));
  } else if (node->op == "-") {
    if (lhs_type == Type::kInt && rhs_type == Type::kInt)
      return builder->CreateSub(lhs_val, rhs_val);
    return builder->CreateFSub(
        builder->CreateSIToFP(lhs_val, builder->getDoubleTy()),
        builder->CreateSIToFP(rhs_val, builder->getDoubleTy()));
  } else if (node->op == "*") {
    if (lhs_type == Type::kInt && rhs_type == Type::kInt)
      return builder->CreateMul(lhs_val, rhs_val);
    return builder->CreateFMul(
        builder->CreateSIToFP(lhs_val, builder->getDoubleTy()),
        builder->CreateSIToFP(rhs_val, builder->getDoubleTy()));
  } else if (node->op == "/") {
    auto div = builder->CreateFDiv(
        builder->CreateSIToFP(lhs_val, builder->getDoubleTy()),
        builder->CreateSIToFP(rhs_val, builder->getDoubleTy()));
    if (lhs_type == Type::kInt && rhs_type == Type::kInt)
      return builder->CreateFPToSI(div, builder->getInt32Ty());
    return div;
  } else
    throw std::logic_error(fmt::format("unsupported operator: {}", node->op));
}

llvm::Value *IRGen::operator()(std::unique_ptr<CallExprNode> &node) {
  auto callee_func = module->getFunction(node->callee);
  if (callee_func == nullptr)
    throw std::logic_error(fmt::format("unknown function: {}", node->callee));
  ExprTypeChecker checker(globals, functions);
  if (callee_func->arg_size() != functions[node->callee].second.size())
    throw std::logic_error("incorrect number of args passed");
  std::vector<llvm::Value *> arg_values;
  auto it = functions[node->callee].second.begin();
  for (auto &arg : node->args) {
    auto val = std::visit(*this, arg);
    auto arg_type = *(it++);
    if (arg_type == Type::kInt)
      arg_values.push_back(builder->CreateFPToSI(val, builder->getInt32Ty()));
    else if (arg_type == Type::kFloat)
      arg_values.push_back(builder->CreateSIToFP(val, builder->getDoubleTy()));
  }
  return builder->CreateCall(callee_func, arg_values);
}
