#include "cmd-calc/ExpressionNode.h"

/**
 * @brief Performs the node's operation (designated by its type),
 * and returns the result of the operation. 
 * 
 * @note Evaluation should be done on the root node of the expression tree,
 * since evaluating a parent will require evaluating child nodes.
 * 
 * @param node The expression node to evaluate
 * @returns the result of the calculation
 */
double ExpressionNode::evaluate(ExpressionNode* node) {
    switch(node->type) {
        case NodeType_Number: return node->number;
        case NodeType_Positive: return evaluate(node->unary.operand);
        case NodeType_Negative: return -evaluate(node->unary.operand);
        case NodeType_Add: return evaluate(node->binary.left) + evaluate(node->binary.right);
        case NodeType_Sub: return evaluate(node->binary.left) - evaluate(node->binary.right);
        case NodeType_Mul: return evaluate(node->binary.left) * evaluate(node->binary.right);
        case NodeType_Div: return evaluate(node->binary.left) / evaluate(node->binary.right);
        case NodeType_Pow: return pow(evaluate(node->binary.left), evaluate(node->binary.right));
        case NodeType_Func:

            switch(node->func.name) {
                case Sqrt: return sqrt(evaluate(node->func.body));
                case Sin: return sinf(evaluate(node->func.body));
                case Cos: return cosf(evaluate(node->func.body));
                case Tan: return tanf(evaluate(node->func.body));
                case Log: return log10f(evaluate(node->func.body));
                case Ln: return logf(evaluate(node->func.body));
                case Log2: return log2f(evaluate(node->func.body));
                case ASin: return asinf(evaluate(node->func.body));
                case ACos: return acosf(evaluate(node->func.body));
                case ATan: return atanf(evaluate(node->func.body));
                case Abs: return abs(evaluate(node->func.body));
                
                default:
                    return evaluate(node->func.body);
            }
    }

    return 0.0;
}