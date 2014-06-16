#include "ExprAST.h"

/// VariableExprAST - Expression class for referencing a variable, like "a".
class VariableExprAST : public ExprAST {

	std::string Name;

public:
  VariableExprAST(const std::string &name) : Name(name) {}

};
