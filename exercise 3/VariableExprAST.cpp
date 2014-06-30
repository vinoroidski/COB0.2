#ifndef VARIABLEEXPRAST_H
#define VARIABLEEXPRAST_H

#include "VariableExprAST.h"

VariableExprAST::VariableExprAST(std::string name, ExprAST *rhs){
	this->name = name;
	this->rhs = rhs;
	//save in map
}

void VariableExprAST::print(){
	std::cout<<name<<"->";
	rhs->print();
}

#endif
