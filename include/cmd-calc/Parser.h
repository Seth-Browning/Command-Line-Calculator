#ifndef PARSER_H
#define PARSER_H

#include <iostream>
#include <string>
#include <math.h>
#include "Lexer.h"
#include "ExpressionNode.h"

using namespace std;

/**
 * @brief Given a `Lexer`, takes the token stream it generated
 * and combines them into a tree of `ExpressionNode`s. This is
 * done to give structure to the mathematical operations.
 * @see Lexer, ExpressionNode
 */
struct Parser {
    Lexer lexer;
    Token current;

    void parser_advance();
    Token peak();
    ExpressionNode* get_expression_tree();
};


#endif