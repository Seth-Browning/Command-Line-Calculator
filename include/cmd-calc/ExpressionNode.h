#ifndef EXPRESSION_NODE_H
#define EXPRESSION_NODE_H

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <math.h>

using namespace std;

/**
 * @brief The type of expression node, which determines what features
 * the node has.
 */
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

/**
 * @brief Predefined functions names.
 */
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
 * @brief Predefined constant names.
 */
enum ConstantNames {
    e,
    pi
};

/**
 * @brief A map from a string to a function's name.
 */
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
 * @brief A Node containing information based on its position in a
 * tree structure, which may include references to other nodes. 
 * Each node can represent a function, a number, or an opertion 
 * (unary or binary).
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

    
    double evaluate(ExpressionNode* node);
    
    ~ExpressionNode() {
        for (ExpressionNode* exprNode : functionArguments) {
            delete exprNode;
        }
    }
};

#endif