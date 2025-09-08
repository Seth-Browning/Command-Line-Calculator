#ifndef PARSER_H
#define PARSER_H

#include <iostream>
#include <string>
#include <math.h>
#include "Lexer.h"
#include "ExpressionNode.h"

using namespace std;

struct Parser {
    Lexer lexer;
    Token current;

    void parser_advance();
    ExpressionNode* get_expression_tree();
};


#endif