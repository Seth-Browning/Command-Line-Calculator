#include "cmd-calc/CharacterChecks.h"

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
 * @brief Gives the lowercase version of a letter.
 * @param inputChar The character to lowercase.
 * @returns The lowercase form of the letter
 */
char to_lowercase(char inputChar) {
    if (inputChar >= 'A' && inputChar <= 'Z') return (inputChar - ('A' - 'a'));
    return inputChar;
}

/**
 * @brief Gives a lowercase version of the given string.
 * @param inputString The string to copy and lowercase.
 * @returns A lowercase copy of the given string.
 */
string to_lowercase(string inputString) {
    string copy = inputString;
    for(int i = 0; i < copy.size(); i++) {
        copy[i] = to_lowercase(copy[i]);
    }
    return copy;
}

