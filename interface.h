/*****************************************************************************************************
* FILE NAME: interface.h
* AUTHOR: Marc Rutland Towse (1834935)
* UNIT: Unix and C Programming
* PURPOSE: to provide forward declarations for interface.c
* REFERENCE: none
* LAST MOD: 26th May 2018
* COMMENTS: also includes data.h
*****************************************************************************************************/


#ifndef interface_h
#define interface_h

#include "data.h"

void acceptInput(char* day, char*choice);
void validateDayInput(char* choice, int* validated);
void validateChoice(char* choice, int* validated);
void convertInput(char* str);
void flush();
void printTerminal(entry* array, int* arrayLength);

#endif
