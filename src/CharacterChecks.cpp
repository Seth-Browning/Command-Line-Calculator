#include "cmd-calc/CharacterChecks.h"


bool is_whitespace(char character) {
    return character == ' ' || character == '\n' || 
        character == '\t' || character == '\r' || 
        character == '\f' || character == '\v';
}


bool is_alpha(char character) {
    return (character >= 'a' && character <= 'z') || (character >= 'A' && character <= 'Z');
}


bool is_number(char character) {
    return (character >= '0' && character <= '9');
}


char to_lowercase(char inputChar) {
    if (inputChar >= 'A' && inputChar <= 'Z') return (inputChar - ('A' - 'a'));
    return inputChar;
}


string to_lowercase(string inputString) {
    string copy = inputString;
    for(int i = 0; i < copy.size(); i++) {
        copy[i] = to_lowercase(copy[i]);
    }
    return copy;
}

string bool_to_string(bool value) {
    return value ? "True" : "False";
}