/* 
 * File:   lexer.h
 * Author: Vinay
 *
 * Created on April 24, 2014, 4:19 PM
 */

#ifndef LEXER_H
#define	LEXER_H

#include <string>
#include <fstream>
#include <vector>
#include <sstream>

#include "../BS_1/Token.h"

using namespace std;

class Lexer {
public:
    Lexer();
    virtual ~Lexer();
    
    void tokenize(string);
    
    vector< vector<Token*> > getStore();
    
private:
    vector< Token* > expressionStore;
    vector< vector<Token*> > tokenizedExpressions;
    
    bool isLiteral(char);
    bool isNumeral(char);
    bool isOperation(char);

};

#endif	/* LEXER_H */

