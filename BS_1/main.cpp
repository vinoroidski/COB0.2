/* 
 * File:   main.cpp
 * Author: Vinay
 *
 * Created on April 24, 2014, 3:55 PM
 */

#include <cstdlib>
#include <iostream>
#include <string>

#include "Screener.h"
#include "Lexer.h"
#include "Parser.h"

using namespace std;

/*
 * 
 */
int main(int argc, char** argv) {
    
    vector< vector<Token*> > store;
    
    Screener testScreener;
    Lexer testLexer;
    
    testScreener.readFile("/cygdrive/d/Tools/BS/BS_1/RichtigBS.txt");
    testScreener.cleanFile();
    testScreener.writeFile("/cygdrive/d/Tools/BS/BS_1/OutputBS.txt");
    
    testLexer.tokenize("/cygdrive/d/Tools/BS/BS_1/OutputBS.txt");
            
    store = testLexer.getStore();
    Parser testParser(store);
    
    //testParser.parse();
    
    return 0;

}

