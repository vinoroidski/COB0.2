#ifndef ROOT_H
#define ROOT_H

#include "ExprAST.h"

class Root : public ExprAST {
	private:
		ExprAST* LHS;
		ExprAST* RHS;
		
	public:
		void print();
		void setLHS(ExprAST*);
		void setRHS(ExprAST*);

};


#endif // ROOT_H
