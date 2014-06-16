#include "NumberExprAST.h"

NumberExprAST::NumberExprAST(int val) : Val(val) {}

NumberExprAST::NumberExprAST(double val) : Val(val) {}

NumberExprAST::NumberExprAST (const NumberExprAST &n){
	this->Val = n.Val;
}

NumberExprAST &NumberExprAST::operator=(const NumberExprAST &n){
	if(this != &n)
		this->Val = n.Val;
	
	return *this;
}

int NumberExprAST::getVal(){
	return this->Val;
	}

void NumberExprAST::setVal(int n){
	this->Val = n;
}

void NumberExprAST::print() {
	std::cout << Val;
}
