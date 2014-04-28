/* 
 * File:   token.cpp
 * Author: Vinay
 * 
 * Created on April 27, 2014, 6:30 PM
 */

#include "../BS_1/Token.h"

Token::Token() {
}

Token::~Token() {
}

Token::Token(char c) {
    
    this->lit = c;
    this->tokenType = operation;
    
}

Token::Token(string word) {
    
    this->lit = word;
    this->tokenType = literal;
    
}

Token::Token(int a) {
    
    this->number = a;
    this->tokenType = constInt;
    
}

Token::Token(double d) {
    
    this->decimalNumber = d;
    this->tokenType = constDouble;
    
}

string Token::getLiteral() {
    return lit;
}

int Token::getNumber() {
    return number;
}

double Token::getNum() {
    return decimalNumber;
}

Token::Type Token::getTokenType() {
    return tokenType;
}

void Token::setLiteral(string fac) {
    lit = fac;
}

void Token::setNumber(int numeric) {
    number = numeric;
}

void Token::setNum(double numeric) {
    decimalNumber = numeric;
}

void Token::setTokenType(Token::Type typ) {
    tokenType = typ;
}