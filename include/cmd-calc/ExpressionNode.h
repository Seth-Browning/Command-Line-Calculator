#ifndef EXPRESSION_NODE_H
#define EXPRESSION_NODE_H

#include <iostream>
#include <string>
#include <math.h>

enum ExpressionNodeKind {
    NodeType_Error,
    NodeType_Number,
    NodeType_Positive,
    NodeType_Negative,
    NodeType_Add,
    NodeType_Sub,
    NodeType_Mul,
    NodeType_Div,
    NodeType_Pow,

    NodeType_Func
};

enum FunctionNames {
    Trivial,
    Sin,
    Cos,
    Tan,
    Sqrt,
    Log,
    Ln,
    Log2,
    ASin,
    ACos,
    ATan,
    ATan2,
    Abs
};

/**
 * @brief A Node that contains information about itself as well
 * as references to other nodes in a tree structure.
 * 
 * @author Seth Browning
 * @date 9/7/2025
 */
class ExpressionNode {
    public:
    ExpressionNodeKind type;

    union {
        double number;
        struct { ExpressionNode* operand; } unary;
        struct { ExpressionNode* left; ExpressionNode* right;} binary;
        struct { ExpressionNode* body; FunctionNames name;} func;
    };

    double evaluate(ExpressionNode* node);
};

#endif