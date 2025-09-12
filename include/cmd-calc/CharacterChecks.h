#ifndef CHARACTER_CHECKS
#define CHARACTER_CHECKS

#include <iostream>
#include <string>

using namespace std;

bool is_whitespace(char character);
bool is_alpha(char character);
bool is_number(char character);
char to_lowercase(char character);
string to_lowercase(string str);


#endif