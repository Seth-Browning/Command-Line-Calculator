#ifndef LEXER_H
#define LEXER_H

#include <iostream>
#include <string>
#include <vector>
#include "Token.h"

using namespace std;

/**
 * @brief Creates tokens from analyzing an input string,
 * consumes inputs when doing so.
 * 
 * @author Seth Browning
 * @date 9/7/2025
 */
class Lexer {
    public:

    // Current Token span
    int start;
    int current;
    
    
    char GetChar(int index);
    string* analysisString;
    Lexer(string* analysisString);
    Token getToken();
    
    private:
    int currentTokenIndex;
    vector<Token> tokens;
    Token lexer_next_token();
};

#endif