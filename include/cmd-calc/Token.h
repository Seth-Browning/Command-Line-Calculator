#ifndef TOKEN_H
#define TOKEN_H

#include <iostream>
#include <string>
#include <map>

using namespace std;

/**
 * @brief Describes what role a token plays and determines
 * the placement of an ExpressionNode in the resulting
 * evaluation tree.
 * 
 * @see ExpressionNode
 */
enum TokenType {
    TokenType_EOF, TokenType_Error,
    TokenType_Ident, TokenType_Number,

    TokenType_Plus, TokenType_Minus,
    TokenType_Star, TokenType_Slash,
    TokenType_Caret,

    TokenType_Assignment, TokenType_Separator,
    TokenType_OpenParen,
    TokenType_CloseParen,
    TokenType_Empty
};

/**
 * @brief Precedence level determins what order operators
 * are evaluated in.
 * 
 * @note `Precedence_Min` is used as a baseline precedence
 * for comparison between operators.
 */
enum Precedence {
    Precedence_Min,     // Special
    Precedence_Term,    // + and -
    Precedence_Factor,  // * and /
    Precedence_Power,   // ^
};

/**
 * @brief A singular unit of mathematical information,
 * telling what kind of token it is and the underlying 
 * text from it's origin string.
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