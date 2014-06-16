#include "ExprAST.h"

/// CallExprAST - Expression class for function calls.
class CallExprAST : public ExprAST {

  std::string Callee;
  std::vector<ExprAST*> Args;

public:
  CallExprAST(const std::string &callee, std::vector<ExprAST*> &args)
    : Callee(callee), Args(args) {}

};
