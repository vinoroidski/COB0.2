#include "PrototypeAST.h"
#include "ExprAST.h"

/// FunctionAST - This class represents a function definition itself.
class FunctionAST {

  PrototypeAST *Proto;
  ExprAST *Body;
  
public:
  FunctionAST(PrototypeAST *proto, ExprAST *body)
    : Proto(proto), Body(body) {}

};
