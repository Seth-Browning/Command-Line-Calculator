#include "cmd-calc/Token.h"

Token::Token(string lexeme, TokenType tokenType) : lexeme(lexeme), tokenType(tokenType) {}

void Token::Print() {
    std::cout << lexeme << endl;
}

ostream& operator<<(ostream& stream, const Token& obj) {
    stream << obj.lexeme;
    return stream;
}
