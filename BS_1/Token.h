/* 
 * File:   token.h
 * Author: Vinay
 *
 * Created on April 27, 2014, 6:30 PM
 */

#ifndef TOKEN_H
#define	TOKEN_H

#include <string>

using namespace std;

    
class Token {
public:
    
    enum Type{literal, constInt, constDouble, operation, id};
    
    Token();
    Token(string);
    Token(int);
    Token(double);
    
    virtual ~Token();
    
    string getLiteral();
    int getNumber();
    double getNum();
    Type getTokenType();
    
    void setLiteral(string);
    void setNumber(int);
    void setNum(double);
    void setTokenType(Type);
    
    
    
private:
    Type tokenType;
    string lit; // !!
    int number;
    double decimalNumber;
    
};

#endif	/* TOKEN_H */

