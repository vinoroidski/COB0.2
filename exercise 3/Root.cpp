#include "Root.h"


void Root::print() {
	
	LHS->print();

	if(RHS)
	RHS->print();

}

void Root::setLHS(ExprAST* lhs) {
	LHS = lhs;
}

void Root::setRHS(ExprAST* rhs) {
	RHS = rhs;
}
