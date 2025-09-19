#include "cmd-calc/Lexer.h"
#include "cmd-calc/CharacterChecks.h"

// bro is really out here doing stuff

/**
 * @brief Gets the character from the lexer's string 
 * at the specified index.
 * 
 * @param index that index of the character to get
 * @return Characters found at index
 */
char Lexer::GetChar(int index) {
    return (*analysisString).at(index);
}

/**
 * @brief Gets the character from the specified lexer at that lexer's
 * `current` value.
 * 
 * @param lexer* pointer to the lexer to fetch the character from.
 * @returns The lexer's `current` character.
 */
char Lexer::GetCurrentLexerChar() {
    if (current >= analysisString->size()) return '\0';
    return GetChar(current);
}

/**
 * @brief Creates a new Token from the lexer with the provided type, with 
 * the lemexe as a span of the characters from `start` to `current` from the lexer.
 * 
 * @param lexer* The lexer to create the Token from.
 * @param type The type to give the new Token.
 * 
 * @returns A new Token with the specified type and generated lexeme.
 */
Token Lexer::lexer_make_token(TokenType type) {
    if (type == TokenType_EOF) {
        return Token("EOF", type);
    }

    return Token(analysisString->substr(start, current - start), type);
}

/**
 * @brief Creates a number token from the provided lexer.
 * 
 * @param lexer* The lexer to use to create the number Token.
 * @returns A new number Token from the lexer, with a lexeme of the number.
 */
Token Lexer::lexer_number() {
    while (is_number( GetCurrentLexerChar() )) {
        current++;
    }

    if (GetCurrentLexerChar() == '.') {
        current++;
        while (is_number(GetCurrentLexerChar())) {
            current++;
        }
    }
    return lexer_make_token(TokenType_Number);
}

/**
 * @brief Creates an Identifier Token from the provided lexer.
 * 
 * @param lexer* The lexer to use to create the identifier Token.
 * @returns A new identifier Token from the lexer, with a lexeme 
 * of the identifier.
 */
Token Lexer::lexer_ident() {
    while (is_alpha(GetCurrentLexerChar())) current++;
    return lexer_make_token(TokenType_Ident);
}

/**
 * @brief Creates a new Token from the lexer and consumes its input.
 * 
 * @returns A new Token from the lexer.
 */
Token Lexer::lexer_next_token() {
    start = current;

    //precheck to make sure that the end of the string hasn't been reached
    if(current >= analysisString->length()) {
        return lexer_make_token(TokenType_EOF);
    }

    while(is_whitespace(GetChar(start))) {
        start++;
    }

    current = start;

    //check again to make sure that there wasn't whitespace before the end
    if(current >= analysisString->length()) {
        return lexer_make_token(TokenType_EOF);
    }

    char currentChar = GetChar(current);
    switch(currentChar) {
        // easy to check for, only need to move after the symbol and then create the token
        case '+': current++; return lexer_make_token(TokenType_Plus);
        case '-': current++; return lexer_make_token(TokenType_Minus);
        case '*': current++; return lexer_make_token(TokenType_Star);
        case '/': current++; return lexer_make_token(TokenType_Slash);
        case '^': current++; return lexer_make_token(TokenType_Caret);
        case '(': current++; return lexer_make_token(TokenType_OpenParen);
        case ')': current++; return lexer_make_token(TokenType_CloseParen);

        // more difficult, but there's a function for that
        case '0': case '1': case '2': case '3': case '4': 
        case '5': case '6': case '7': case '8': case '9':
            return lexer_number();

        default:
            if(is_alpha(GetChar(current))) return lexer_ident();

            current++;
            return lexer_make_token(TokenType_Error);
    }
}

/**
 * @brief Checks if the next token's type is valid to come immediately
 * after the current token.
 * 
 * @returns Whether or not the next token can follow the current token.
 */
bool token_type_can_follow(TokenType currentTokenType, TokenType nextTokenType) {
    switch (currentTokenType) {
        case TokenType_OpenParen:
        case TokenType_CloseParen:
        case TokenType_Plus:
        case TokenType_Minus:
        case TokenType_Star:
        case TokenType_Slash:
        case TokenType_Caret:
            return !(nextTokenType == TokenType_Ident || nextTokenType == TokenType_Plus || nextTokenType == TokenType_Minus || nextTokenType == TokenType_OpenParen || nextTokenType == TokenType_Number);
    }

    return true;
}

/**
 * @brief Goes through the lexer's token list and checks for any obvious
 * errors, like syntax and parenthesies errors.
 * 
 * @returns Error status based on the token list.
 */
ErrorStatus Lexer::check_token_list() {
    if (tokens.size() <= 1) return ErrorStatus_Empty;

    vector<char> parenthesisStack;

    for (int i = 0; i < tokens.size() - 1; i++) {
        Token currentToken = tokens.at(i);
        Token nextToken = tokens.at(i + 1);
        TokenType currentTokenType = currentToken.tokenType;
        TokenType nextTokenType = nextToken.tokenType;
        
        // enforces token ordering rules
        switch (currentToken.tokenType) {
            case TokenType_Empty:
            case TokenType_Error:
                return ErrorStatus_SyntaxError;
            
            case TokenType_OpenParen:
                parenthesisStack.push_back('(');
                if ( token_type_can_follow(currentTokenType, nextTokenType) ) {
                    return ErrorStatus_SyntaxError;
                }
                break;

            case TokenType_CloseParen:
                if (parenthesisStack.empty()) return ErrorStatus_ParenthesisError;
                parenthesisStack.pop_back();
                if ( token_type_can_follow(currentTokenType, nextTokenType) ) {
                    return ErrorStatus_SyntaxError;
                }
                break;

            case TokenType_Star:
            case TokenType_Slash:
            case TokenType_Caret:
                if (i == 0) return ErrorStatus_SyntaxError;
            case TokenType_Plus:
            case TokenType_Minus:
                // An operation can be followed by a number, a +, a -, or a (
                if ( token_type_can_follow(currentTokenType, nextTokenType) ) {
                    return ErrorStatus_SyntaxError;
                }
                break;
            
            case TokenType_Number:
                // a number can be followed by a *, /, +, -, ^, (, ), EOF, or ident
                break;
        }
    }

    // More ( than )
    if (!parenthesisStack.empty()) return ErrorStatus_ParenthesisError;

    return ErrorStatus_None;
}

// Constructor to give the lexer its input
/**
 * @brief Lexes the given string into a stream of tokens
 * and performs checks to make sure that they are in a valid
 * order.
 * 
 * @param analysisString The string to analyze.
 */
Lexer::Lexer(string* analysisString) : 
    analysisString(analysisString), 
    start(0), 
    current(0),
    currentTokenIndex(0)
{
    tokens.push_back(lexer_next_token());

    while(tokens.at(tokens.size() - 1).tokenType != TokenType_EOF) {
        tokens.push_back(lexer_next_token());
    }

    errorStatus = check_token_list();
}

/**
 * @brief Gets the current token from the lexer, causes the
 * current token to advance.
 * 
 * @returns The current token from the Lexer.
 */
Token Lexer::getToken() {
    Token holder = tokens.at(currentTokenIndex);
    currentTokenIndex++;
    return holder;
}

/**
 * @brief Gets the next token from the lexer without consuming it.
 * 
 * @returns The next token from the Lexer.
 */
Token Lexer::peekToken() {
    // deal with the end of the list by yourself, I don't wanna hear it
    return tokens.at(currentTokenIndex + 1);
}

/**
 * @brief Gets the previous token from the lexer without consuming
 * any input.
 * 
 * @returns The previous token from the Lexer.
 */
Token Lexer::previousToken() {
    return tokens.at(currentTokenIndex - 1);
}

/**
 * @brief Gets the lexer's error status.
 * 
 * @return Error status.
 */
ErrorStatus Lexer::getErrorStatus() {
    return errorStatus;
}