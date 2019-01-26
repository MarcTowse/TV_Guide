/*****************************************************************************************************
* FILE NAME: comparison.c
* AUTHOR: Marc Rutland Towse (18345935)
* UNIT: Unix and C Programming
* PURPOSE: to provide qsort() with its comparing algorithms for alphabetical and chronological order
* REFERENCE: www.tutorialspoint.com/c_standard_library/c_function_strcmp.htm
* LAST MOD: 18th May 2018
* COMMENTS: none
*****************************************************************************************************/

/*includes*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "comparison.h"
#include "tvguide.h"
#include "data.h"
#include "interface.h"

/*****************************************************************************************************
* NAME: compareName
* PURPOSE: to be called recursively by qsort()
* IMPORTS: a void pointer to an entry, a void pointer to an entry
* EXPORTS: an intger value n
* PRE ASSERTIONS: the two entry values imported (through a void pointer) are valid
* POST ASSERTIONS: the first values position in the new array compared to its last (higher or lower)
* REMARKS: man pages on strcmp() were useful to writing this code
******************************************************************************************************/

int compareName(const void *a, const void *b) 
{
    /*declarations + two malloced strings to hold the data without altering the original*/
    int n = 0;
    char* A = ( char* )malloc( nameSize*sizeof ( char ) ); 
    char* B = ( char* )malloc( nameSize*sizeof ( char ) ); 

    /*copy the data to be tested to the strings then convert it to lowercase*/
    strcpy( A, ( ( entry* )a )->name );
    strcpy( B, ( ( entry* )b )->name );
    convertInput( A );
    convertInput( B );

    /*compare to see if A is above, below or same placement as B*/
    n = (strcmp( A, B ) );

    /*if strings match*/
    if ( n == 0 )
    {
        /*compare the times as a secondary decider*/
        n = compareTime( a, b );
    }

    /*free the strings and return if a is above or below b in the array*/
    free( A );
    free( B );
    return( n );
}

/*****************************************************************************************************
* NAME: compareTime
* PURPOSE: to be called recursively by qsort()
* IMPORTS: a void pointer to an entry, a void pointer to an entry
* EXPORTS: an integer value n
* PRE ASSERTIONS: the two entry values imported (through a void pointer) are valid
* POST ASSERTIONS: a in reference to b's position in the array (higher or lower)
* REMARKS: similar method as used in compareName
******************************************************************************************************/

int compareTime(const void *a, const void *b) 
{
    /*declarations*/
    int i=1;
    /*zero and zero2 are needed to lengthen the shorter times*/
    char *first,*second, zero[6] = "0", zero2[6] = "0";

    /*if the time is too short*/
    if ( strlen( ( ( entry* )a )->time ) == 4 )
    {
        /*copy the input into a new array with a 0 at the start*/
        for ( i=1; i<5; i++ )
        {
            zero[i] = ( ( entry* )a )->time[i-1];
        }
        /*first becomes the required time*/
        first = zero;
    }
    else
    {
        first = ( ( entry* )a )->time;
    }
    /*repeats the code with first for second*/
    if ( strlen( ( ( entry* )b )->time ) == 4 )
    {
        for ( i=1; i<5; i++ )
        {
            zero2[i] = ( ( entry* )b )->time[i-1];
        }
        second = zero2;
    }
    else
    {
        second = ( ( entry* )b )->time;
    }

    /*return whether first is chronologically earlier or later than second*/
    return ( strcmp( first, second ) );
}
