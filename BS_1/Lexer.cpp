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
    string element = "";
    string expression;
    
    ifstream myFile;
    ofstream myFileOut;
    
    myFile.open(inputFilePath.c_str());
    
    while (!myFile.eof()) {

        myFile >> expression;

        if (expression.size() > 0) {
            
            for(int i = 0; i < expression.size(); i++) { // we go through the expression
                c = expression.at(i);
                
                if(isLiteral(c)) { // we found a literal
                    
                    i = checkForLiteral(expression, element, i);
                    
                } else if(isNumeral(c)) { // we found a number
                    
                    i = checkForNumeral(expression, element, i);
                    
                } else {
                    
                    i = checkForOperation(expression, element, i);
                    
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


int Lexer::checkForLiteral(string expression, string element, int i){
              
    char c = expression.at(i++);
    
    element.push_back(c);

    for(int j = i; j < expression.size(); j++) { // we keep saving till end of literal

        c = expression.at(j);
        if(!isLiteral(c)) {

            if(!isNumeral(c)) {

                Token* ttoken = new Token(element);
                expressionStore.push_back(ttoken);

                element.clear();
                return (j - 1);

            }

        }
        element.push_back(c);

    }

}

int Lexer::checkForNumeral(string expression, string element, int i) {
                    
    stringstream str;
    
    int valueOfNumber;
    
    char c = expression.at(i);
    element.push_back(c);
    
    if(i+1==expression.size()){
        
    valueOfNumber = atoi (element.c_str());

            element.clear();
            Token* ttoken = new Token(valueOfNumber);
            expressionStore.push_back(ttoken);
        
    }else{
        
        for(int j = i+1; j < expression.size(); j++) { // we save till end of number
            c = expression.at(j);

            if(c == '.') { // number has decimal points

                return ( checkForDecimal(expression, element, j, str) );

            } else if(isNumeral(c)) { // if not decimal, keep saving in number

                element.push_back(c);

            } else {

                // integer saved

                valueOfNumber = atoi (element.c_str());

                element.clear();
                Token* ttoken = new Token(valueOfNumber);
                expressionStore.push_back(ttoken);

                return (j - 1);

            }    

        }
        
    }
    
}

int Lexer::checkForDecimal(string expression, string element, int j, stringstream& str) {
    
    double valueOfNum;
    
    char c = expression.at(j);
    element.push_back(c);

    for(int k = j + 1; k < expression.size(); k++) { // we read till end of decimals
                                                 // or check for error
        c = expression.at(k);
        j = k;

        if(c == '.') {

            // Error - more than one comma
            cout << "Error : zwei punkte!" << endl;

        } else {

            if(isNumeral(c)) {

                element.push_back(c);

            } else {
                
                break;

            }

        }

    }
    

    // double saved
    str << element; 
    str >> valueOfNum;
    

    element.clear();
    Token* ttoken = new Token(valueOfNum);
    expressionStore.push_back(ttoken);
    
    if(isNumeral(c)){
      return j;    
    }
    
    return (j - 1);
    
}

int Lexer::checkForOperation(string expression, string element, int i) {
    
    char c = expression.at(i);
    if(c == ':') {
        
        c = expression.at(++i);
        if(c == '=') {
            
            element = ":=";
                   
            Token* ttoken = new Token(element);
            ttoken->setTokenType(Token::operation);
            expressionStore.push_back(ttoken);
            
            return i;
            
            
        } else {
             // TO DO otherwise error
        }
        
    }
    
    if(isOperation(c)) {
                    
        Token* ttoken = new Token(c);
        expressionStore.push_back(ttoken);
        
        return i;

    } else {
        
        // TO DO error for unrecognized element
        
    }
    
}