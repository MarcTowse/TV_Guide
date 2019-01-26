/*****************************************************************************************************
* FILE NAME: tvguide.h
* AUTHOR: Marc Rutland Towse (18345935)
* UNIT: Unix and C Programming
* PURPOSE: contains the forward declarations for tvguide.c and defines for other files
* REFERENCE: none
* LAST MOD: 27th May 2018
* COMMENTS: none
*****************************************************************************************************/


#ifndef tvguide_h
#define tvguide_h

#define nameSize 250
#define daySize 10
#define timeSize 6

#include "linkedList.h"
#include "data.h"

int main( int argc, char* argv[] );
void convertToArray( LinkedList* list, entry* array );
void filter( entry* array, int* arrayLength, char* day );
void sort( entry* array, int* arrayLength, char* choice );
void freeAll( LinkedList* list, int total );
void printReadError( int linesRead );

#endif
