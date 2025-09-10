#include "cmd-calc/Parser.h"

/**
 * @brief Advances the parser to the next token.
 */
void Parser::parser_advance() {
    current = lexer.getToken();
}

/**
 * @brief Gives the lowercase version of a letter.
 * @param inputChar The character to lowercase.
 * @returns The lowercase form of the letter
 */
char toLowercase(char inputChar) {
    if (inputChar >= 'A' && inputChar <= 'Z') return (inputChar - ('A' - 'a'));
    return inputChar;
}

/**
 * @brief Gives a lowercase version of the given string.
 * @param inputString The string to copy and lowercase.
 * @returns A lowercase copy of the given string.
 */
string toLowerCase(string inputString) {
    string copy = inputString;
    for(int i = 0; i < copy.size(); i++) {
        copy[i] = toLowercase(copy[i]);
    }
    return copy;
}


ExpressionNode* parser_parse_expression(Parser* parser, Precedence prev_prec); // function signature given so that helper parse functions could call `parser_parse_expression`.


// This was done because a map didn't work, I tried.
/**
 * @brief Gives a precedence value depending on the given TokenType.
 * @param tokenType The tokenType to give the precedence value for
 * @returns The Precedence value.
 */
Precedence precedence_lookup(TokenType tokenType) {
    switch (tokenType) {
        case TokenType_Plus: return Precedence_Term;
        case TokenType_Minus: return Precedence_Term;
        case TokenType_Star: return Precedence_Factor;
        case TokenType_Slash: return Precedence_Factor;
        case TokenType_Caret: return Precedence_Power;
        default: return Precedence_Min;
    }
    return Precedence_Min;
}

// Also done because a map didn't work, I was annoyed too.
/**
 * @brief Gives the function name, if any, of an input string.
 * @param name The name of the potential function.
 * @returns The name of the function, is there was none then 
 * `Trivial` was given instead.
 */
FunctionNames function_name_lookup(string name) {
    string lowerName = toLowerCase(name);
    if (lowerName == "sin") return Sin;
    if (lowerName == "cos") return Cos;
    if (lowerName == "tan") return Tan;
    if (lowerName == "sqrt") return Sqrt;
    if (lowerName == "ln") return Ln;
    if (lowerName == "log2") return Log2;
    if (lowerName == "log") return Log;
    if (lowerName == "abs") return Abs;
    if (lowerName == "atan") return ATan;
    if (lowerName == "acos") return ACos;
    if (lowerName == "asin") return ASin;

    return Trivial;
}

/**
 * @brief Gives an error node
 * @returns An error node
 */
ExpressionNode* error_node() {
    ExpressionNode* ret = new ExpressionNode();
    ret->type = NodeType_Error;
    return ret;
}

/**
 * @brief Parses a number from the parser and gives an expression node.
 * @param parser The parser to generate the number expression node from.
 * @returns An expression node with a number.
 */
ExpressionNode* parser_parse_number(Parser* parser) {
    ExpressionNode* ret = new ExpressionNode();
    
    ret->type = NodeType_Number;
    ret->number = stod(parser->current.lexeme);
    // I'm masochistic enough to have written this function myself if it didn't
    // already exist.

    parser->parser_advance();
    return ret;
}

/**
 * @brief Parses a binary operator from the parser and a left expression node 
 * and generates the right node inside of it.
 * @param parser The parser to get the right node from, consumes input.
 * @param oper The operator token so the node is correct.
 * @param left The left expression node that will be placed before the operator 
 * in the expression tree.
 * @returns The operator's expression node.
 */
ExpressionNode* parser_parse_infix_expr(Parser* parser, Token oper, ExpressionNode* left) {
    ExpressionNode* ret = new ExpressionNode();
    switch(oper.tokenType) {
        case TokenType_Plus: ret->type = NodeType_Add; break;
        case TokenType_Minus: ret->type = NodeType_Sub; break;
        case TokenType_Star: ret->type = NodeType_Mul; break;
        case TokenType_Slash: ret->type = NodeType_Div; break;
        case TokenType_Caret: ret->type = NodeType_Pow; break;
    }
    ret->binary.left = left;
    ret->binary.right = parser_parse_expression(parser, precedence_lookup(oper.tokenType));
    return ret;
}

// Parenthesies act as an exception to the order of operations, and
// can replace any leaf node without changing the shape of the tree as a whole.
// It's a difficult thing to grasp, but it acts like a leaf node even if it isn't one.
/**
 * @brief Parses an expression that doesn't change the expression
 * tree's general form.
 * @param parser The parser to generation the expression node from
 * @returns The new expresison node.
 */
ExpressionNode* parser_parse_terminal_expr(Parser* parser) {
    ExpressionNode* ret = 0;
    
    if (parser->current.tokenType == TokenType_Number) {
        
        ret = parser_parse_number(parser);

    } else if (parser->current.tokenType == TokenType_OpenParen) {
        
        // parse the expression inside the parenthesies and then move 
        // out of them
        parser->parser_advance();
        ret = parser_parse_expression(parser, Precedence_Min);
        if (parser->current.tokenType == TokenType_CloseParen) {
            parser->parser_advance();
        }

    // A positive plus, not an additon plus: +5
    } else if (parser->current.tokenType == TokenType_Plus) {
        
        parser->parser_advance();
        ret = new ExpressionNode();
        ret->type = NodeType_Positive;
        ret->unary.operand = parser_parse_terminal_expr(parser);

    // A negative dash instead of a subtraction dash: -5
    } else if (parser->current.tokenType == TokenType_Minus) {
        
        parser->parser_advance();
        ret = new ExpressionNode();
        ret->type = NodeType_Negative;
        ret->unary.operand = parser_parse_terminal_expr(parser);

    // If the token is an indentifier
    } else if (parser->current.tokenType == TokenType_Ident) {
        
        string identifier = parser->current.lexeme;
        parser->parser_advance();

        // Check if the identifier has the form of a function
        if(parser->current.tokenType == TokenType_OpenParen) {
            
            ExpressionNode* func_ret = new ExpressionNode();
            
            // parse the expression inside of the function body
            // and then move out of it
            parser->parser_advance();
            func_ret = parser_parse_expression(parser, Precedence_Min);
            if (parser->current.tokenType == TokenType_CloseParen) {
                parser->parser_advance();
            }

            ret = new ExpressionNode();
            ret->type = NodeType_Func;
            ret->func.body = func_ret;
            ret->func.name = function_name_lookup(identifier);

        // The identifier is Euler's constant
        } else if(identifier == "e") {

            ret = new ExpressionNode();
            ret->type = NodeType_Number;
            ret->number = 2.71828182845904523536;

        // The identifier is pi
        } else if(identifier == "pi") {

            ret = new ExpressionNode();
            ret->type = NodeType_Number;
            ret->number = 3.14159265358979323846;

        // Unknown identier, default its value to 0
        } else {

            ret = new ExpressionNode();
            ret->type = NodeType_Number;
            ret->number = 0.0;
            parser->parser_advance();

        }

    } else return error_node();

    // Implicit Multiplication
    if (parser->current.tokenType == TokenType_Number || 
        parser->current.tokenType == TokenType_OpenParen) {
        
        ExpressionNode* new_ret = new ExpressionNode();
        new_ret->type = NodeType_Mul;
        new_ret->binary.left = ret;
        new_ret->binary.right = parser_parse_expression(parser, Precedence_Factor);
        ret = new_ret;

    }

    return ret;
}


/**
 * @brief Parses the expression node into a tree of nodes for evaluation.
 * @param parser The parser that will be parsing its expression.
 * @param prev_prec The Precedence to begin with.
 * @note Beginning precedence whould be the precedence of the first token.
 * @returns The root expression node from the parser.
 */
ExpressionNode* parser_parse_expression(Parser* parser, Precedence prev_prec) {
    // Recursive Function
    ExpressionNode* left = parser_parse_terminal_expr(parser);
    Token current_operator = parser->current;
    Precedence current_precedence = precedence_lookup(current_operator.tokenType);

    while (current_precedence != Precedence_Min) {
        // Three cases
        if (prev_prec >= current_precedence) {
            break;
        }

        parser->parser_advance();
        left = parser_parse_infix_expr(parser, current_operator, left);
        current_operator = parser->current;
        current_precedence = precedence_lookup(current_operator.tokenType);
    }
    return left;
}

ExpressionNode* Parser::get_expression_tree() {
    return parser_parse_expression(this, Precedence_Min);
}