#include "cmd-calc/Lexer.h"

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
char GetCurrentLexerChar(Lexer* lexer) {
    if (lexer->current >= (*lexer->analysisString).size()) return '\0';
    return lexer->GetChar(lexer->current);
}

/**
 * @brief Checks if the specifies character is whitespace.
 * 
 * @param character The character that is being checked.
 * @returns If that character is whitespace.
 */
bool is_whitespace(char character) {
    return character == ' ' || character == '\n' || 
        character == '\t' || character == '\r' || 
        character == '\f' || character == '\v';
}

/**
 * @brief Checks if the specifies character is an Alphabetical character,
 * either lowercase or uppercase.
 * 
 * @param character The character that is being checked.
 * @returns If the character is a letter.
 */
bool is_alpha(char character) {
    return (character >= 'a' && character <= 'z') || (character >= 'A' && character <= 'Z');
}

/**
 * @brief Checks if the specifies character is a number character.
 * 
 * @param Character The character to check.
 * @returns If the character is a number;
 */
bool is_number(char character) {
    return (character >= '0' && character <= '9');
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
Token lexer_make_token(Lexer *lexer, TokenType type) {
    if (type == TokenType_EOF) {
        return Token("EOF", type);
    }

    return Token(lexer->analysisString->substr(lexer->start, lexer->current - lexer->start), type);
}

/**
 * @brief Creates a number token from the provided lexer.
 * 
 * @param lexer* The lexer to use to create the number Token.
 * @returns A new number Token from the lexer, with a lexeme of the number.
 */
Token lexer_number(Lexer *lexer) {
    while (is_number( GetCurrentLexerChar(lexer) )) {
        lexer->current++;
    }

    if (GetCurrentLexerChar(lexer) == '.') {
        lexer->current++;
        while (is_number(GetCurrentLexerChar(lexer))) {
            lexer->current++;
        }
    }
    return lexer_make_token(lexer, TokenType_Number);
}

/**
 * @brief Creates an Identifier Token from the provided lexer.
 * 
 * @param lexer* The lexer to use to create the identifier Token.
 * @returns A new identifier Token from the lexer, with a lexeme 
 * of the identifier.
 */
Token lexer_ident(Lexer *lexer) {
    while (is_alpha(GetCurrentLexerChar(lexer))) lexer->current++;
    return lexer_make_token(lexer, TokenType_Ident);
}

/**
 * @brief Transforms the boolean values into string representations.
 * 
 * @param value Either true or false.
 * @returns Either the string "True" or "False"
 */
string bool_to_string(bool value) {
    return value ? "True" : "False";
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
        return lexer_make_token(this, TokenType_EOF);
    }

    while(is_whitespace(GetChar(start))) {
        start++;
    }

    current = start;

    //check again to make sure that there wasn't whitespace before the end
    if(current >= analysisString->length()) {
        return lexer_make_token(this, TokenType_EOF);
    }

    char currentChar = GetChar(current);
    switch(currentChar) {
        // easy to check for, only need to move after the symbol and then create the token
        case '+': current++; return lexer_make_token(this, TokenType_Plus);
        case '-': current++; return lexer_make_token(this, TokenType_Minus);
        case '*': current++; return lexer_make_token(this, TokenType_Star);
        case '/': current++; return lexer_make_token(this, TokenType_Slash);
        case '^': current++; return lexer_make_token(this, TokenType_Caret);
        case '(': current++; return lexer_make_token(this, TokenType_OpenParen);
        case ')': current++; return lexer_make_token(this, TokenType_CloseParen);

        // more difficult, but there's a function for that
        case '0': case '1': case '2': case '3': case '4': 
        case '5': case '6': case '7': case '8': case '9':
            return lexer_number(this);

        default:
            if(is_alpha(GetChar(current))) return lexer_ident(this);
            return lexer_make_token(this, TokenType_Error);
    }
}

// Constructor to give the lexer its input
/**
 * @brief Constructor that gives the lexer the string it will analyze
 * @param analysisString The string to analyze.
 */
Lexer::Lexer(string* analysisString) : 
    analysisString(analysisString), start(0), current(0),
    currentTokenIndex(0) {
    tokens.push_back(lexer_next_token());

    while(tokens.at(tokens.size() - 1).tokenType != TokenType_EOF) {
        tokens.push_back(lexer_next_token());
    }
}


Token Lexer::getToken() {
    Token holder = tokens.at(currentTokenIndex);
    currentTokenIndex++;
    return holder;
}