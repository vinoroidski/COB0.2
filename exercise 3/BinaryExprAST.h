#ifndef BinaryExprAST_H
#define BinaryExprAST_H

#include "ExprAST.h"

/// BinaryExprAST - Expression class for a binary operator.
class BinaryExprAST : public ExprAST {

  std::string Op;
  ExprAST *LHS, *RHS;

public:
  BinaryExprAST(std::string op, ExprAST *lhs, ExprAST *rhs);
  BinaryExprAST(const BinaryExprAST &n);
  BinaryExprAST &operator =(const BinaryExprAST &n);

  void print();

};

#endif // BinaryExprAST_H
