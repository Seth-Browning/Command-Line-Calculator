#ifndef EXPRESSION_NODE_H
#define EXPRESSION_NODE_H

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <math.h>

using namespace std;

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

enum ConstantNames {
    e,
    pi
};

const map<string, FunctionNames> toFunctionNames = {
    {"sin", Sin},
    {"cos", Cos},
    {"tan", Tan},
    {"sqrt", Sqrt},
    {"log", Log},
    {"ln", Ln},
    {"log2", Log2},
    {"asin", ASin},
    {"acos", ACos},
    {"atan", ATan},
    {"abs", Abs}
};

const map<string, ConstantNames> toConstantNames = {
    {"e", e},
    {"pi", pi}
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

    vector<ExpressionNode*> functionArguments = {};

    ~ExpressionNode() {
        for (ExpressionNode* exprNode : functionArguments) {
            delete exprNode;
        }
    }

    double evaluate(ExpressionNode* node);
};

#endif