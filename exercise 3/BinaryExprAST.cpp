#include "BinaryExprAST.h"


BinaryExprAST::BinaryExprAST(std::string op, ExprAST *lhs, ExprAST *rhs) : Op(op), LHS(lhs), RHS(rhs) {}

BinaryExprAST::BinaryExprAST (const BinaryExprAST &n){
		this->Op = n.Op;
		this->LHS = n.LHS;
		this->RHS = n.RHS;
}


BinaryExprAST &BinaryExprAST::operator=(const BinaryExprAST &n){
	if(this != &n) {
		this->Op = n.Op;
		this->LHS = n.LHS;
		this->RHS = n.RHS;
	}
	return *this;
}

void BinaryExprAST::print() {

	LHS->print();
	std::cout << " " << Op << " ";
	RHS->print(); 
	std::cout << std::endl;

}
