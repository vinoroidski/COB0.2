#ifndef NUMBEREXPRAST_H
#define NUMBEREXPRAST_H

#include "ExprAST.h"

class NumberExprAST : public ExprAST {
	private:
		double Val;
		
	public:
		NumberExprAST(int val);
		NumberExprAST(double val);
		NumberExprAST(const NumberExprAST &n);
		NumberExprAST &operator =(const NumberExprAST &n);
		int getVal();
		void setVal(int n);
		void print();
};


#endif // NUMBEREXPRAST_H
