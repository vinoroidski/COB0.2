/* 
 * File:   screener.cpp
 * Author: Vinay
 * 
 * Created on April 27, 2014, 6:26 PM
 */

#include "Screener.h"

Screener::Screener() {
}

Screener::~Screener() {
}

void Screener::readFile(string filePath) {

    char letter;
    ifstream myFile;

    myFile.open(filePath.c_str());

    while (!myFile.eof()) {

        myFile >> noskipws >> letter;

        if (!myFile.eof())
            input.push_back(letter);

    }

    myFile.close();

}

void Screener::cleanFile() {
    
    vector<char> store;
    
    for (vector<char>::iterator it = input.begin(); it != input.end(); it++) {

        if (*it != '\r')
            store.push_back(*it);

    }

    for (vector<char>::iterator it = store.begin(); it != store.end(); it++) {

        if (*it == '/') {

            it++;

            if (*it == '/') {

                it++;

                for (vector<char>::iterator it2 = it; it2 != store.end(); it2++) {

                    // FehlerBehandlung fehlt
                    // 2 2 + 3 -> 22+3

                    if (*it2 == '\n') {

                        it = it2;
                        break;

                    }

                }

            } else if (*it == '*') {

                it++;

                for (vector<char>::iterator it3 = it; it3 != store.end(); it3++) {

                    if (*it3 == '*') {

                        it3++;

                        if (*it3 == '/') {

                            it = it3 + 1;
                            it3 = store.end();
                            break;

                        }

                    }

                }

            } else {

                output.push_back('/');
                if(*it == ' ') it--;
                else output.push_back(*it);

            }

        } else if (*it == ' ') {

            for (vector<char>::iterator it4 = it; it4 != store.end(); it4++) {

                if (*it4 != ' ') {

                    it = it4 - 1;
                    break;

                }

            }

        } else if (*it == '\n') {
            
            it++;
            
            if(*it == '\n') 
                it--;
            else {
                output.push_back('\n');
                it--;
            } 
                
                
        } else {

            output.push_back(*it);

        }

    }
    
    store.clear();
    for(vector<char>::iterator it = output.begin(); it != output.end(); it++) {
        
        if(*it == '\n') {
            
            it++;
            
            if(*it == '\n')
                it--;
            else {
                store.push_back('\n');
                store.push_back(*it);
            }
            
        } else {
            store.push_back(*it);
        }
        
    }
    
    output.clear();
    for(vector<char>::iterator it = store.begin(); it != store.end(); it++) 
        output.push_back(*it);

}

void Screener::writeFile(string filePath) {

    if (output.size() > 0) {

        ofstream myFile;

        myFile.open(filePath.c_str());

        for (vector<char>::iterator it = output.begin(); it != output.end(); it++) {

            myFile << *it;

        }

        myFile.close();

    }

}