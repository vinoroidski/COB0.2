/* 
 * File:   parser.cpp
 * Author: Vinay
 * 
 * Created on April 24, 2014, 6:26 PM
 */

#include "Parser.h"

Parser::Parser() {
}

Parser::Parser(vector< vector<Token*> > tokensList) {
    
    tokenStore = tokensList;
    
}

Parser::~Parser() {
}

void Parser::parse(string filePath) {

    ofstream myFile;
    double value;
    myFile.open(filePath.c_str());
    
    for (int i = 0; i < tokenStore.size(); i++) {
        
        value = result(tokenStore.at(i));
        if(value > -9998) // if -9998, we have operation of type pi := 8
            myFile << value << endl;
        else if(value == -9999)
            myFile << "No valid operation found!" << endl;

    }

    myFile.close();
    
}

double Parser::addition(double a, double b) {
    return (a + b);   
}

double Parser::subtraction(double a, double b) {
    return (a - b);
}

double Parser::multiplication(double a, double b) {
    return (a * b);
}

double Parser::division(double a, double b) {
    return (a / b);
}

double Parser::result(vector<Token*> factors) {
    
    int result = 0;
    
    Token::Type type1 = factors.at(0)->getTokenType();
    Token::Type type2 = factors.at(1)->getTokenType();
    Token::Type type3 = factors.at(2)->getTokenType();
    
    Token* factor1 = factors.at(0);
    Token* factor2 = factors.at(1);
    Token* factor3 = factors.at(2);
    
    if(type2 == Token::operation) {
        if(type1 == type3 == Token::constInt && factor2->getLiteral() != ":=") {
            
            result = evaluateInt(factor1->getNumber(), factor3->getNumber(), factor2->getLiteral());
            
        }   else if(type1 == type3 == Token::constDouble) {
            
            result = evaluateDouble(factor1->getNum(), factor3->getNum(), factor2->getLiteral());
            
        }   else if(type1 == Token::literal && type3 == Token::constInt && factor2->getLiteral() == ":=") {
            
            
            
        }   else if(type1 == Token::literal && type3 == Token::constDouble && factor2->getLiteral() == ":=") {
            
            
            
        }   else if(type1 == type3 == Token::literal && factor2->getLiteral() == ":=") {
            
            
            
        }
            
    } else
        result = -9999;
    
    return result;
    
}

double Parser::evaluateInt(int a, int b, string op) {
    
    int result;
    
    if(op == "+")
        result = (int) addition(a, b);
    if(op == "-")
        result = (int) subtraction(a, b);
    if(op == "*")
        result = (int) multiplication(a, b);
    if(op == "/")
        result = (int) division(a, b);
    
    return result;
    
}

double Parser::evaluateDouble(double a, double b, string op) {
    
    double result;
    
    if(op == "+")
        result = addition(a, b);
    if(op == "-")
        result = subtraction(a, b);
    if(op == "*")
        result = multiplication(a, b);
    if(op == "/")
        result = division(a, b);
    
    return result;
    
}