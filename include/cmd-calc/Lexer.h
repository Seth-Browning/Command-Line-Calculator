#ifndef LEXER_H
#define LEXER_H

#include <iostream>
#include <string>
#include <vector>
#include "Token.h"

using namespace std;

/**
 * @brief Error statuses that can be given from the lexer pre-checks
 */
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
        Lexer(string* analysisString);

        char GetChar(int index);
        Token getToken();
        Token peekToken();
        ErrorStatus getErrorStatus();

        
        private:
        Token lexer_next_token();

        // Token Batching span.
        int start = 0;
        int current = 0;
        string* analysisString = nullptr;
        
        int currentTokenIndex = 0;
        vector<Token> tokens;
        ErrorStatus errorStatus = ErrorStatus_Unchecked;
        ErrorStatus check_token_list();

        char GetCurrentLexerChar();
        Token lexer_make_token(TokenType type);
        Token lexer_number();
        Token lexer_ident();
};

#endif