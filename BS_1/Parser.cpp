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
        if(value != 0) // if 0, we have operation of type pi := 8
            myFile << value << endl;

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
    
    Token* factor;
    double parameter1;
    double parameter2;
    Token* param1;
    Token* param2;
    double result = 1;
    string operation;
    bool lookUpVariable = false;
    
    factor = factors.at(0);
    param1 = factor;
    
    if(factor->getTokenType() == Token::constDouble)
        parameter1 = factor->getNum();
    else 
        parameter1 = factor->getNumber();
    
    factor = factors.at(1);
    operation = factor->getLiteral();
    
    factor = factors.at(2);
    param2 = factor;
    
    if(factor->getTokenType() == Token::constDouble)
        parameter2 = factor->getNum();
    else 
        parameter2 = factor->getNumber();
    
    if(operation != ":=") {
        
        if(operation == "+")
            result = addition(parameter1, parameter2);
        else if(operation == "-")
            result = subtraction(parameter1, parameter2);
        else if(operation == "*")
            result = multiplication(parameter1, parameter2);
        else if(operation == "/")
            result = division(parameter1, parameter2);
        
    } else {
        
        result = 0;
        store[param1] = param2;
        
    }
    
    return result;
    
}

/*
int Parser::op(string a) {
    
    for(int i = 0; i <  a.size(); i++) {
        
        switch(a.at(i)) {
            
            case '+'    :   return 1;
                            break;
                
            case '-'    :   return 2;
                            break;
            
            case '*'    :   return 3;
                            break;
               
            case '/'    :   return 4;
                            break;
                            
            case '='   :   return 5;
                            break;
                
            default     :   break;
                            
        }
        
    }
    
}

vector<string> Parser::factors(string a) {
    
    vector<string> result;
    string tmp;
    
    for(int i = 0; i < a.size(); i++) {
        
        if(a.at(i) != '+' && a.at(i) != '-' && a.at(i) != '*' && a.at(i) != '/' && a.at(i) != '=') {
            tmp.push_back(a.at(i));
        } else {
            result.push_back(tmp);
            tmp.clear();
        }
        
        if(a.size() == ++i) {
            result.push_back(tmp);
            tmp.clear();
        } else i--;
        
    }
    
    return result;
    
}*/