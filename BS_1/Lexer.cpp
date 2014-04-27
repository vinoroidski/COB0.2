/* 
 * File:   lexer.cpp
 * Author: Vinay
 * 
 * Created on April 24, 2014, 4:19 PM
 */

#include "Lexer.h"

Lexer::Lexer() {
}

Lexer::~Lexer() {
}

void Lexer::tokenize(string inputFilePath) {
    
    char c;
    stringstream str;
    string element = "";
    string expression;
    
    int valueOfNumber;
    double valueOfNum;
    
    ifstream myFile;
    ofstream myFileOut;
    
    myFile.open(inputFilePath.c_str());
    
    while (!myFile.eof()) {

        myFile >> expression;

        if (expression.size() > 0) {
            
            for(int i = 0; i < expression.size(); i++) { // we go through the expression
                c = expression.at(i);
                
                if(isLiteral(c)) { // we found a literal
                    
                    element.push_back(c);
                    
                    for(int j = i; j < expression.size(); j++) { // we keep saving till end of literal
                        
                        c = expression.at(j);
                        if(!isLiteral(c)) {

                            if(!isNumeral(c)) {
                                
                                Token* ttoken = new Token(element);
                                expressionStore.push_back(ttoken);
                                
                                element.clear();
                                i = j - 1;
                                break;

                            }

                        }
                        
                    }
                    
                } else if(isNumeral(c)) { // we found a number
                    
                    element.push_back(c);
                    
                    for(int j = i; j < expression.size(); j++) { // we save till end of number
                        c = expression.at(j);
                        
                        if(c == ',') { // number has decimal points
                            
                            element.push_back(c);
                            
                            for(int k = j; k < expression.size(); k++) { // we read till end of decimals
                                                                         // or check for error
                                c = expression.at(k);
                                
                                if(c == ',') {
                                    
                                    // Error - more than one comma
                                    
                                } else {
                                  
                                    if(isNumeral(c)) {
                                        
                                        element.push_back(c);
                                        
                                    } else {
                                        
                                        j = k - 1;
                                        break;
                                        
                                    }
                                    
                                }
                                
                            }
                                
                            // double saved
                            str >> element;
                            str << valueOfNum;
                            
                            element.clear();
                            Token* ttoken = new Token(valueOfNum);
                            expressionStore.push_back(ttoken);
                            
                            i = j - 1;
                            break;
                            
                        } else if(isNumeral(c)) { // if not decimal, keep saving in number
                            
                            element.push_back(c);
                            
                        } else {
                            
                            // integer saved
                            str >> element;
                            str << valueOfNumber;
                            
                            element.clear();
                            Token* ttoken = new Token(valueOfNumber);
                            expressionStore.push_back(ttoken);
                            
                            i = j - 1;
                            break;
                            
                        }
                        
                    }
                    
                } else if(isOperation(c)) {
                    
                    Token* ttoken = new Token(c);
                    ttoken->setTokenType(Token::operation);
                    expressionStore.push_back(ttoken);
                    
                }
                
                // TO DO - string a = 2 - string zuweisung
                // type type - saves int, double, ...
                
            }
            
        }
        
        tokenizedExpressions.push_back(expressionStore);
        expressionStore.clear();
        
    }

    myFile.close();
    
}

bool Lexer::isLiteral(char c) {
    
    int a = int (c);
    if(a < 64 || (a > 91 && a < 96) || a > 122) return false;
    else return true;
    
}

bool Lexer::isNumeral(char c) {
    
    int a = int(c);
    if(a > 47 && a < 58) return true;
    else return false;
    
}

bool Lexer::isOperation(char c) {
    
    switch(c) {
        
        case '='    :   return true;
            
        case '+'    :   return true;   
            
        case '-'    :   return true;   
            
        case '*'    :   return true;   
            
        case '/'    :   return true;   
            
        default     :   return false;
    
    }
    
}

vector < vector <Token*> > Lexer::getStore() {
    
    return tokenizedExpressions;
    
}