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
    
    void parse(string);
    
private:
    map<Token*, Token*> store;
    
    vector < vector<Token*> > tokenStore;
    
    double addition(double, double);
    double subtraction(double, double);
    double multiplication(double, double);
    double division(double, double);
    
    double result(vector <Token*>);
    
};

#endif	/* PARSER_H */

/*
 * Diego = +, -, /, * methods. return int, take two parameters. declare in header and cpp
 * Vinay = charToInt and formatting of final input file
 * 
 */