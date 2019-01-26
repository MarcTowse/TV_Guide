/*****************************************************************************************************
* FILE NAME: interface.c
* AUTHOR: Marc Rutland Towse (1834595)
* UNIT: Unix and C Programming
* PURPOSE: contains all functions that get input from the user (via the terminal,
*       not the command-line) and output to the terminal. 
* REFERENCE: none
* LAST MOD: 26th May 2018
* COMMENTS: none
*****************************************************************************************************/

/*includes*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "data.h"
#include "interface.h"

/*****************************************************************************************************
* NAME: acceptInput 
* PURPOSE: provides the instructions to the user and accepts input then calls the appropriate 
*       validating functions
* IMPORTS: the day as a string, and choice as a string
* EXPORTS: none
* PRE ASSERTIONS: none
* POST ASSERTIONS: a valid day and choice have been provided
* REMARKS: has multiple outputs depending on users attempt number
******************************************************************************************************/

void acceptInput( char* day, char* choice )
{
    /*integer used to keep track of attempts and if they're valid*/
    int validated = 0;

    /*keep asking for a day until validated*/
    while ( validated <= 0 ) 
    {
        /*provide two message depending on if its the users first or multiple attempt*/
        if ( validated == 0 )
        {
            printf( "\nPlease select the required day\n" );
        }
        else
        {
            printf( "\nOops! try that again, making sure you are selecting a day of the week.\n" );
        }
        printf( "-Monday\n-Tuesday\n-Wednesday\n-Thursday\n-Friday\n-Saturday\n-Sunday\n" );
        printf( "choice: " );

        /*scan the line in, convert it to lower case, validate it*/
        fgets( day, 11, stdin );
        convertInput( day );
        validateDayInput( day, &validated );
    }

    /*reset validate for choice, then execute the while loop the same with choice instead of day*/
    validated = 0;

    while( validated <= 0 )
    {
        if( validated == 0 )
        {
            printf( "\nHow would you like this to be sorted?\n" );
        }
        else
        {
            printf( "\nOops! try that again, making sure you select one of the options.\n" );
        }
        printf( "-Time\n-Name\n" ); 
        printf( "choice: " );
        fgets( choice, 6, stdin );
        convertInput( choice );
        validateChoice( choice, &validated );
    }

    /*output the users final validated choices*/
    printf( "You selected %s and would like this sorted by %s\n", day, choice );
}

/*****************************************************************************************************
* NAME: validateDayInput
* PURPOSE: validates the day input
* IMPORTS: the day as a string and the flag for validation
* EXPORTS: none
* PRE ASSERTIONS: none
* POST ASSERTIONS: if the day is valid
* REMARKS: validate works on a -1, 0 and 1 flag instead of just true false
******************************************************************************************************/

void validateDayInput( char* day, int* validated )
{
    /*show that an input has been attempted but has not yet been validated*/
    *validated = -1;

    /*if the whole string was not read in flush out the remaining characters*/
    if( day[strlen( day )-1] != '\n' )
    {
        flush(  );
    }
    else
    {
        /*rmove the new line character*/
        strtok( day, "\n" ); 

        /*if the input matches one of the days of the week mark it as being validated*/
        if  ( ( strcmp( day, "monday" ) == 0 ) || ( strcmp( day, "tuesday" ) == 0 ) || ( strcmp( day, "wednesday" ) == 0 ) || ( strcmp( day, "thursday" ) == 0 ) || ( strcmp( day, "friday" ) == 0 ) || ( strcmp( day, "saturday" ) == 0 ) || ( strcmp( day, "sunday" ) == 0 ) )
        {
            *validated = 1;
        }
    }
}

/*****************************************************************************************************
* NAME: validateChoide
* PURPOSE: validate the choice input
* IMPORTS: choice as a string and the flag for validation
* EXPORTS: none
* PRE ASSERTIONS: none
* POST ASSERTIONS: if the choice is valid
* REMARKS: validate works on a -1, 0 and 1 flag instead of just true false
******************************************************************************************************/

void validateChoice( char* choice, int* validated )
{
    /*show that an input has been attempted but has not yet been validated*/
    *validated = -1;

    /*if the hwole string was not read in flush out the remaining characters*/
    if ( choice[4] != '\n' )
    {
        flush(  );
    }
    else
    {
        /*remove the new line character*/
        strtok( choice, "\n" );

        /*if the input matches one of the choices mark it as being validated*/
        if ( ( strcmp( choice, "time" ) == 0 ) ||( strcmp( choice, "name" ) == 0 ) )
        {
            *validated = 1;
        }
    }
}

/*****************************************************************************************************
* NAME: convertInput
* PURPOSE: converts a string to being lower case
* IMPORTS: str as a string
* EXPORTS: none
* PRE ASSERTIONS: none
* POST ASSERTIONS: the string is lowercase now, characters unchanged
* REMARKS:
******************************************************************************************************/

void convertInput( char* str )
{
    /*checks each character*/
    while( *str != '\0' )
    {
        /*if ranging from A-Z convert to a-z*/
        if ( ( *str>63 )&&( *str<91 ) )
        {
            *str = *str + 32;
        }

        /*increment the string*/
        str++;
    }
}

/*****************************************************************************************************
* NAME: flush
* PURPOSE: flush out the stdin
* IMPORTS: none
* EXPORTS: none
* PRE ASSERTIONS: stdin needs flushing
* POST ASSERTIONS: stdin is flushed
* REMARKS:
******************************************************************************************************/

void flush(  )
{
    int ch;

    /*read the stdin buffer until its empty*/
    while ( ch != '\n' )
    {
        ch = fgetc( stdin );
    }
}

/*****************************************************************************************************
* NAME: printTerminal
* PURPOSE: print the array output to the terminal
* IMPORTS: entry pointer array and the array length as an integer
* EXPORTS: none
* PRE ASSERTIONS: the array data is valid and the array length is correct
* POST ASSERTIONS: the data has been outputed to the terminal 
* REMARKS:
******************************************************************************************************/

void printTerminal(entry* array, int* arrayLength)
{
    int i;

    /*iterate through every array slot wanted*/
    for ( i=0; i<*arrayLength; i++ )
    {
        /*if the time is too short add a space before printing, otherwise print normally*/
        if ( strlen( array[i].time ) == 4 )
        {
            printf(" %s - %s\n", array[i].time, array[i].name);
        }
        else
        {
            printf("%s - %s\n", array[i].time, array[i].name);
        }
    }
}









