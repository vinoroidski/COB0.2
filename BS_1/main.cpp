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

    testScreener.readFile("RichtigBS.txt");
    testScreener.cleanFile();
    testScreener.writeFile("OutputBS.txt");

    testLexer.tokenize("OutputBS.txt");

    store = testLexer.getStore();

    for (int i = 0; i < store.size(); i++) {
        for (int j = 0; j < store.at(i).size(); j++) {
            Token* token = store.at(i).at(j);
            switch (token->getTokenType()) {

                case Token::literal: cout << "Literal: " << token->getLiteral() << endl;
                    break;
                case Token::constInt: cout << "constInt: " << token->getNumber() << endl;
                    break;
                case Token::constDouble: cout << "constDouble: " << token->getNum() << endl;
                    break;
                case Token::operation: cout << "Operation: " << token->getLiteral() << endl;
                    break;
                default: cout << "Error - Unknown Type" << endl;

            }

        }
        cout << endl;
    }

    //    Parser testParser(store);

    //testParser.parse();

    return 0;

}

