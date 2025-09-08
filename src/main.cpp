#include <iostream>
#include <string>
#include <vector>

#include "cmd-calc/Token.h"
#include "cmd-calc/Lexer.h"
#include "cmd-calc/ExpressionNode.h"
#include "cmd-calc/Parser.h"


int main() {

    string expression;

    cout << "> ";
    getline(cin, expression);

    // /*
    while (expression != "quit") {
   
        Lexer lexer(&expression);
        Token currentToken = lexer.lexer_next_token();
        Parser parser = {lexer, currentToken};
        ExpressionNode* expression_tree = parser.get_expression_tree();
        
        cout << expression_tree->evaluate(expression_tree) << endl << endl;
    
        delete expression_tree;

        cout << "> ";
        getline(cin, expression);
    }
    // */

    return 0;
}