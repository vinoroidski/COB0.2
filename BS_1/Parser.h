/* 
 * File:   parser.h
 * Author: Vinay
 *
 * Created on April 24, 2014, 6:26 PM
 */

#ifndef PARSER_H
#define	PARSER_H

#include <vector>
#include <sstream>
#include <string>
#include <fstream>
#include <map>

#include "Lexer.h"

using namespace std;

class Parser {
public:
    Parser();
    Parser(vector < vector <Token*> >);
    virtual ~Parser();
    
    void parse();
    
private:
    string expression;
    map<string, string> store;
    
    vector < vector<Token*> > tokenStore;
    
    float addition(float, float);
    float subtraction(float, float);
    float multiplication(float, float);
    float division(float, float);
    
    int op(string);
    vector<string> factors(string);
    
    float result(string);
    
};

#endif	/* PARSER_H */

/*
 * Diego = +, -, /, * methods. return int, take two parameters. declare in header and cpp
 * Vinay = charToInt and formatting of final input file
 * 
 */