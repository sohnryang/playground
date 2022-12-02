#pragma once

#include <map>
#include <memory>
#include <string>
#include <utility>
#include <vector>

#include <llvm/IR/Function.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/Module.h>
#include <llvm/IR/Value.h>

class ExprNode {
public:
  virtual ~ExprNode() = default;
  virtual llvm::Value *
  codegen(std::shared_ptr<llvm::LLVMContext> context,
          std::shared_ptr<llvm::Module> module,
          std::shared_ptr<llvm::IRBuilder<>> builder,
          std::map<std::string, llvm::Value *> &named_values) = 0;
  virtual std::string to_string() = 0;
};

template <typename T> class LiteralExprNode : public ExprNode {
private:
  T value;

public:
  LiteralExprNode(T value);
  llvm::Value *
  codegen(std::shared_ptr<llvm::LLVMContext> context,
          std::shared_ptr<llvm::Module> module,
          std::shared_ptr<llvm::IRBuilder<>> builder,
          std::map<std::string, llvm::Value *> &named_values) override;
  std::string to_string() override;
};

class VariableExprNode : public ExprNode {
private:
  std::string name;

public:
  VariableExprNode(const std::string &name);
  llvm::Value *
  codegen(std::shared_ptr<llvm::LLVMContext> context,
          std::shared_ptr<llvm::Module> module,
          std::shared_ptr<llvm::IRBuilder<>> builder,
          std::map<std::string, llvm::Value *> &named_values) override;
  std::string to_string() override;
};

class BinaryExprNode : public ExprNode {
private:
  std::string op;
  std::unique_ptr<ExprNode> lhs, rhs;

public:
  BinaryExprNode(std::string op, std::unique_ptr<ExprNode> lhs,
                 std::unique_ptr<ExprNode> rhs);
  llvm::Value *
  codegen(std::shared_ptr<llvm::LLVMContext> context,
          std::shared_ptr<llvm::Module> module,
          std::shared_ptr<llvm::IRBuilder<>> builder,
          std::map<std::string, llvm::Value *> &named_values) override;
  std::string to_string() override;
};

class CallExprNode : public ExprNode {
private:
  std::string callee;
  std::vector<std::unique_ptr<ExprNode>> args;

public:
  CallExprNode(const std::string &callee,
               std::vector<std::unique_ptr<ExprNode>> args);
  llvm::Value *
  codegen(std::shared_ptr<llvm::LLVMContext> context,
          std::shared_ptr<llvm::Module> module,
          std::shared_ptr<llvm::IRBuilder<>> builder,
          std::map<std::string, llvm::Value *> &named_values) override;
  std::string to_string() override;
};

class StatementNode {
public:
  virtual ~StatementNode() = default;
  virtual llvm::Value *
  codegen(std::shared_ptr<llvm::LLVMContext> context,
          std::shared_ptr<llvm::Module> module,
          std::shared_ptr<llvm::IRBuilder<>> builder,
          std::map<std::string, llvm::Value *> &named_values) = 0;
  virtual std::string to_string() = 0;
};

class PrototypeNode : public StatementNode {
private:
  std::string name;
  std::string return_type;
  std::vector<std::pair<std::string, std::string>> args;

public:
  PrototypeNode(const std::string &name,
                std::vector<std::pair<std::string, std::string>> args,
                std::string return_type);
  const std::string &get_name() const;
  llvm::Function *
  codegen(std::shared_ptr<llvm::LLVMContext> context,
          std::shared_ptr<llvm::Module> module,
          std::shared_ptr<llvm::IRBuilder<>> builder,
          std::map<std::string, llvm::Value *> &named_values) override;
  std::string to_string() override;
};

class FunctionNode : public StatementNode {
private:
  std::unique_ptr<PrototypeNode> proto;
  std::unique_ptr<ExprNode> func_body;
  bool extern_func;

public:
  FunctionNode(std::unique_ptr<PrototypeNode> proto,
               std::unique_ptr<ExprNode> func_body);
  FunctionNode(std::unique_ptr<PrototypeNode> proto);
  llvm::Function *
  codegen(std::shared_ptr<llvm::LLVMContext> context,
          std::shared_ptr<llvm::Module> module,
          std::shared_ptr<llvm::IRBuilder<>> builder,
          std::map<std::string, llvm::Value *> &named_values) override;
  std::string to_string() override;
};
