#ifndef TOKEN_H
#define TOKEN_H

#include <iostream>
#include <string>
#include <map>

using namespace std;

enum TokenType {
    TokenType_EOF, TokenType_Error,
    TokenType_Ident, TokenType_Number,

    TokenType_Plus, TokenType_Minus,
    TokenType_Star, TokenType_Slash,
    TokenType_Caret,
    TokenType_OpenParen,
    TokenType_CloseParen,
    TokenType_Empty
};

enum Precedence {
    Precedence_Min,     // Special
    Precedence_Term,    // + and -
    Precedence_Factor,  // * and /
    Precedence_Power,   // ^
};

/**
 * @brief A singular unit from a string that hold information.
 * 
 * @author Seth Browning
 * @date 9/7/2025
 */
class Token {
    public:
    string lexeme;
    TokenType tokenType;
    
    Token(string lexeme, TokenType tokenType);
    void Print();
    
    static Token Empty() {
        return Token("", TokenType_Empty);
    }
    

    friend ostream& operator<<(ostream& os, const Token& obj);
};


#endif