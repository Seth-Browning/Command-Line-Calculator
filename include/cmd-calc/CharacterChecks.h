#ifndef CHARACTER_CHECKS
#define CHARACTER_CHECKS

#include <iostream>
#include <string>

using namespace std;

// ********************************************************
// **                     Summary                        **
// ********************************************************
// 
// Some helper functions used to determine the type of a 
// character and gives some operations for them.


/**
 * @brief Checks if the specifies character is whitespace.
 * 
 * @param character The character that is being checked.
 * @returns If that character is whitespace.
 */
bool is_whitespace(char character);

/**
 * @brief Checks if the specifies character is an 
 * Alphabetical character, either lowercase or uppercase.
 * 
 * @param character The character that is being checked.
 * @returns If the character is a letter.
 */
bool is_alpha(char character);

/**
 * @brief Checks if the specifies character is a number character.
 * 
 * @param Character The character to check.
 * @returns If the character is a number;
 */
bool is_number(char character);

/**
 * @brief Gives the lowercase version of a letter.
 * @param inputChar The character to lowercase.
 * @returns The lowercase form of the letter
 */
char to_lowercase(char character);

/**
 * @brief Gives a lowercase version of the given string.
 * @param inputString The string to copy and lowercase.
 * @returns A lowercase copy of the given string.
 */
string to_lowercase(string str);

/**
 * @brief Transforms the boolean values into string representations.
 * 
 * @param value Boolean value.
 * @returns Either the string "True" or "False"
 */
string bool_to_string(bool value);


#endif