#ifndef LEXER_H
#define LEXER_H

#include <iostream>
#include <string>
#include <vector>
#include "Token.h"

using namespace std;

/**
 * @brief Error status that give information about the
 * Lexer's generated token stream.
 */
enum ErrorStatus {
    ErrorStatus_Unchecked,
    ErrorStatus_None,
    ErrorStatus_Empty,
    ErrorStatus_SyntaxError,
    ErrorStatus_ParenthesisError
};

/**
 * @brief Given an input string, generates mathematical tokens
 * and performs validation checks.
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
        Token previousToken();
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