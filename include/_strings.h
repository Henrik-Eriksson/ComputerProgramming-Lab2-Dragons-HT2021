// File: _strings.h 
// Author(s): Henrik Eriksson, Johan Sollenius
// Description: 
// This file contains the public interface for the _strings module. 
// contains a few functions to handle string operations. [_strings.c]

#ifndef _STRINGS_H
#define _STRINGS_H

//This function has two strings as input parameters
//Checks if the strings start witch matching letters ignore uppercase and lowercase differences,
//returns 1 if both strings matches else 0
int equalStrings(char* str1, char* str2);

//This function only have one string as input parameter
//Checks wether the string is strictly only alphabetical, A-Z/a-z
//Returns 1 if true else 0 if false
int isAlphabetic(char* str);

//This function only have one string as input parameter
//Transforms all lowercase chars to uppercase in string
void toUpperCase(char* str);
#endif 
