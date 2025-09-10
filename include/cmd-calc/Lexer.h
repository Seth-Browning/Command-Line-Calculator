#ifndef LEXER_H
#define LEXER_H

#include <iostream>
#include <string>
#include <vector>
#include "Token.h"

using namespace std;

enum ErrorStatus {
    ErrorStatus_Unchecked,
    ErrorStatus_None,
    ErrorStatus_Empty,
    ErrorStatus_SyntaxError,
    ErrorStatus_ParenthesisError
};

/**
 * @brief Creates tokens from analyzing an input string,
 * consumes inputs when doing so.
 * 
 * @author Seth Browning
 * @date 9/7/2025
 */
class Lexer {
    public:
        char GetChar(int index);
        Lexer(string* analysisString);
        Token getToken();
        ErrorStatus getErrorStatus();

        // Token Batching span.
        int start;
        int current;
    
        string* analysisString;
    private:
        Token lexer_next_token();
        
        ErrorStatus errorStatus = ErrorStatus_Unchecked;
        int currentTokenIndex;
        vector<Token> tokens;
        ErrorStatus check_token_list();
};

#endif