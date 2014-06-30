#ifndef VARIABLEEXPRAST_H
#define VARIABLEEXPRAST_H

#include "VariableExprAST.h"

VariableExprAST::VariableExprAST(std::string name, ExprAST *rhs){

	this->next = NULL;

	this->name = name;
	this->rhs = rhs;
	//save in map
}

void VariableExprAST::setNext(ExprAST* next) {
	this->next = next;
}

void VariableExprAST::print(){
	std::cout<<name<<"->";
	rhs->print();
}

#endif
