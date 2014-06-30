#include "ExprAST.h"

/// VariableExprAST - Expression class for referencing a variable, like "a".
class VariableExprAST : public ExprAST {

private:
	std::string name;
	ExprAST *rhs;

public:
  VariableExprAST(std::string name, ExprAST *rhs);
  void print();

};
