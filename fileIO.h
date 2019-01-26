/*****************************************************************************************************
* FILE NAME: fileIO.h
* AUTHOR: Marc Rutland Towse (18345935)
* UNIT: Unix and C Programming
* PURPOSE: contains all the forward declarations for fileIO.c
* REFERENCE: none
* LAST MOD: 26th may 2018
* COMMENTS: data.h is needed for the struct variables
*****************************************************************************************************/


#ifndef fileIO_h
#define fileIO_h

#include "data.h"

void fileRead( LinkedList* list, char* read, int* errorRead, int* linesRead );
void readFunction( FILE* readPtr, LinkedList* list, int* errorRead, int* linesRead );
void removeWhiteSpace( char* name );
int validateName( char* name, int* linesRead );
int validateDay( char* dayInput );
int validateTime( char* time );
void fileWrite( entry* array, int* arrayLength, char* write );
void writeFunction( entry* array, int* arrayLength, FILE* writePtr);

#endif
