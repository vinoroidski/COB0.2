#ifndef EXPRAST_H
#define EXPRAST_H

#include <string>
#include <iostream>

class ExprAST{

public:
    virtual ~ExprAST() {}
    virtual void print() = 0;
};

#endif // EXPRAST_H
