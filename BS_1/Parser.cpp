/* 
 * File:   parser.cpp
 * Author: Vinay
 * 
 * Created on April 24, 2014, 6:26 PM
 */

#include "Parser.h"

Parser::Parser() {
}

Parser::Parser(vector< vector<Token*> > store) {
    
    tokenStore = store;
    
}

Parser::~Parser() {
}

void Parser::parse() {
    
}

float Parser::addition(float a, float b) {
    return (a + b);   
}

float Parser::subtraction(float a, float b) {
    return (a - b);
}

float Parser::multiplication(float a, float b) {
    return (a * b);
}

float Parser::division(float a, float b) {
    return (a / b);
}

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
    
}

float Parser::result(string a) {
    
    float result = -1;
    
    stringstream str;
    vector<float> factor;
    
    vector<string> numbers;
    int operat;
    float tmp;
    
    operat = op(a);
    numbers = factors(a);
    
    if(operat != 5) { 
    
        for(int i = 0; i < numbers.size(); i++) {
            
            if(store.find(numbers.at(i)) != store.end())
                str << store.at(numbers.at(i));
                
            else 
                str << numbers.at(i);
            
            str >> tmp;

            factor.push_back(tmp);

            str << "";
            str.clear();
            
        }

        if(operat == 1) {
            result = addition(factor.at(0), factor.at(1));
        } else if (operat == 2) {
            result = subtraction(factor.at(0), factor.at(1));
        } else if (operat == 3) {
            result = multiplication(factor.at(0), factor.at(1));
        } else if (operat == 4) {
            result = division(factor.at(0), factor.at(1));
        }
    
    } else {
        
        store[numbers.at(0)] = numbers.at(1);
        
    }
    
    return result;
    
}