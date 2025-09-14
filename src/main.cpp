#include <iostream>
#include <string>
#include <vector>

#include "cmd-calc/Token.h"
#include "cmd-calc/Lexer.h"
#include "cmd-calc/ExpressionNode.h"
#include "cmd-calc/Parser.h"

// sample file change for branching

int main() {

    string expression;

    cout << "> ";
    getline(cin, expression);

    // /*
    while (expression != "quit") {
   
        Lexer lexer(&expression);

        // I'm not sure if this is the best way to do this, but I think it's
        // fine for now.
        if (lexer.getErrorStatus() == ErrorStatus_None) {
            Token currentToken = lexer.getToken();
            Parser parser = {lexer, currentToken};
            ExpressionNode* expression_tree = parser.get_expression_tree();
            
            cout << expression_tree->evaluate(expression_tree) << endl << endl;
        
            delete expression_tree;
        } else {
            ErrorStatus error = lexer.getErrorStatus();
            cout << "Error " << error << ": ";
            switch(error) {
                case ErrorStatus_Empty:
                    cout << "Empty Input" << endl;
                    break;
                case ErrorStatus_ParenthesisError:
                    cout << "Parenthesis Error. Are you missing a parenthesis?" << endl;
                    break;
                case ErrorStatus_SyntaxError:
                    cout << "Syntax Error" << endl;
                    break;

                default:
                    cout << "Unknown Error" << endl;
            }
        }

        cout << "> ";
        getline(cin, expression);
    }
    // */

    return 0;
}