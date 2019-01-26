/*****************************************************************************************************
 * FILE NAME: fileIO.c
 * AUTHOR: Marc Rutland Towse (18345935)
 * UNIT: Unix and C Programming
 * PURPOSE: contains all the functions that read and write to files
 * REFERENCE: general error handling taken from laboratory 5
 *      remove white space idea taken from tutorialspoint.com/c_standard_library/c_function_isspace.htm
 * LAST MOD: 26th may 2018
 * COMMENTS: none
 *****************************************************************************************************/

/*includes*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "linkedList.h"
#include "fileIO.h"
#include "data.h"
#include "boolean.h"
#include "tvguide.h"
#include "interface.h"

/*****************************************************************************************************
* NAME: fileRead 
* PURPOSE: to succesfully opena nd close a file stream
* IMPORTS: LinkedList pointer list, name of the file to read from as a string, integer errorRead 
*       and integer linesRead
* EXPORTS: none
* PRE ASSERTIONS: list, errorRead and linesRead have been initialised correctly and read has the 
*       correct file to read from inside
* POST ASSERTIONS: the file will be read or atleast attempted to be read
* REMARKS:
******************************************************************************************************/
void fileRead( LinkedList* list, char* read, int* errorRead, int* linesRead )
{
    /*open the stream to the desired file*/
    FILE* readPtr = fopen( read, "r" );

    /*error checking for the stream*/
    if ( readPtr != NULL )
    {
        /*call the function that read from the file*/
        readFunction( readPtr, list, errorRead, linesRead );
    }
    else
    {
       perror( "Error opening file" );
    }

    /*error checking on if the file read failed*/
    if ( ferror( readPtr ) )
    {
        perror( "Error Reading from file" );
    }

    /*close the stream*/
    fclose( readPtr );
}

/*****************************************************************************************************
* NAME: readFunction
* PURPOSE: read lines from a data file then allocate them into a linked list via a struct
* IMPORTS: a file pointer to the desired read file, LinkedList pointer list, errorRead as an integer
*       and linesRead as an integer
* EXPORTS: none
* PRE ASSERTIONS: the correct file pointer has been given, list errorRead and linesRead are all 
*       initialised correctly
* POST ASSERTIONS: the file has been read or attempted to be read, either an error will be thrown or
*       the list will be populated with valid data, linesRead will increment as the file is read
* REMARKS:
******************************************************************************************************/

void readFunction( FILE* readPtr, LinkedList* list, int* errorRead, int* linesRead )
{
    /*declarations and a malloc*/
    int done=FALSE;
    char* str = ( char* )malloc( nameSize*sizeof ( char ) );

    /*read the first line and continue to do so until done = true*/
    do
    {
        /*increment number of lines read*/
        (*linesRead)++;

        /*read a line and check if fgets returns NULL*/
        if ( fgets( str, nameSize, readPtr ) == NULL )
        {
            /*if the first read failed set it as an error then set done to true*/
            if ( *linesRead == 1 )
            {
                *errorRead = TRUE;
            }
            done = TRUE;
        }
        else
        {
            /*declare and malloc the structs*/
            entry* show = ( entry* )malloc( sizeof ( entry ) );
            show -> name = ( char* )malloc( nameSize*sizeof ( char ) );
            show -> day = ( char* )malloc( daySize*sizeof ( char ) );
            show -> time = ( char* )malloc( timeSize*sizeof ( char ) );

            /*set the name*/
            strcpy( show -> name, str );

            /*read the next line and increment lines read*/
            fgets( str, nameSize, readPtr );
            (*linesRead)++;

            /*scan 2 strings from the last read line*/
            sscanf( str, "%s%s", show->day, show->time );

            /*validate the 3 fields of the struct and then insert it into the list*/
            if ( ( validateName( show -> name, linesRead ) ) && ( validateDay( show -> day ) ) && ( validateTime( show -> time ) ) )
            {
                insertFirst( list, show );
            }
            /*if data corrupted free the list to date and error = true*/
            else
            {
                free( show -> name );
                free( show -> day );
                free( show -> time );
                free( show );
                freeAll( list, list->count );
                *errorRead = TRUE;
                done = TRUE;
            }
        }
    } while ( !done );

    /*free str*/
    free( str );
}

/*****************************************************************************************************
* NAME: fileWrite
* PURPOSE: to succesfully open and close a file
* IMPORTS: entry pointer array, the array length as an integer and a file name as a string
* EXPORTS: none
* PRE ASSERTIONS: that the array, file name and arraylength are valid and correct 
* POST ASSERTIONS: the output will be printed to the correct file
* REMARKS:
******************************************************************************************************/

void fileWrite( entry* array, int* arrayLength , char* write )
{
    /*create the stream to the desired file*/   
    FILE* writePtr = fopen( write, "w" );

    /*error checking for the stream*/
    if ( writePtr != NULL )
    {
        /*call the function that writes to the file*/
        writeFunction( array, arrayLength, writePtr );
    }
    else
    {
       perror( "Error opening file" );
    }

    /*error checking on if the write failed*/
    if ( ferror( writePtr ) )
    {
        perror( "Error writing to file" );
    }
    /*close the stream*/
    fclose( writePtr );
}

/*****************************************************************************************************
* NAME: writeFunction
* PURPOSE: print the array output to a desired file location
* IMPORTS: entry pointer array, the array length as an integer, the file stream
* EXPORTS: none
* PRE ASSERTIONS: the array and array length are valid and correct, the file pointer points to the
*       correct location
* POST ASSERTIONS: the desired output has been printed to the correct file
* REMARKS: algorithm based on output to terminal
******************************************************************************************************/

void writeFunction( entry* array, int* arrayLength, FILE* writePtr )
{
    int i;

    /*iterate through every array slot wanted*/
    for ( i=0; i<*arrayLength; i++ )
    {
        /*if the time is too short add a space before printing, otherwise print normally*/
        if ( strlen( array[i].time ) == 4 )
        {
            fprintf( writePtr, " %s - %s\n", array[i].time, array[i].name);
        }
        else
        {
            fprintf( writePtr, "%s - %s\n", array[i].time, array[i].name);
        }
    }
}

/*****************************************************************************************************
* NAME: vlaidateName
* PURPOSE: to validate the name
* IMPORTS: the name as a string and the number of lines read as an integer
* EXPORTS: validated as an integer
* PRE ASSERTIONS: none
* POST ASSERTIONS: whether the string name is valid or not
* REMARKS:
******************************************************************************************************/

int validateName( char* name, int* linesRead )
{
    int validated = FALSE;

    /*trims whitespace from the begining and end of the string*/
    removeWhiteSpace( name );

    /*decrements linesRead*/
    (*linesRead)--;

    /*check if the name is not empty then increment linesRead and validated becomes true*/
    if ( strlen( name ) >= 1 )
    {
        validated = TRUE;
        (*linesRead)++;
    }

    /*return validated*/
    return ( validated );
}

/*****************************************************************************************************
* NAME: removeWhiteSpace
* PURPOSE: to remove white space from the start and end of a string
* IMPORTS: the name as a string
* EXPORTS: none
* PRE ASSERTIONS: none
* POST ASSERTIONS: the white space is removed from either end of the string
* REMARKS:
******************************************************************************************************/

void removeWhiteSpace( char* name )
{
    /*declarations and initialisations*/
    int i=0;
    char ch = name[i];
    
    /*until the first none whitespace character is hit*/
    while ( isspace( ch ) )
    {
        /*move the string back into its self but one place over then update ch*/
        memmove( name, name+1, strlen( name ) );
        ch = name[i];
    }
    
    /*move ch to the other end of the string*/
    i = strlen( name )-1;
    ch = name[i];

    /*while ch is white space*/
    while ( isspace( ch ) )
    {
        /*cut off the white space and reassign ch*/
        name[i] = '\0';
        i--;
        ch = name[i];
    }
}

/*****************************************************************************************************
* NAME: validateDay
* PURPOSE: to validate the day
* IMPORTS: day as a string
* EXPORTS: validated as an integer
* PRE ASSERTIONS: none
* POST ASSERTIONS: whether the string is valid or not
* REMARKS:
******************************************************************************************************/

int validateDay( char* dayInput )
{
    /*declarations*/
    int validated = FALSE;

    /*convert to lowercase*/
    convertInput( dayInput );

    /*check that it matches one of the 7 days then set validated to true if theres a match*/
    if  ( ( strcmp( dayInput, "monday" ) == 0 ) || ( strcmp( dayInput, "tuesday" ) == 0 ) || ( strcmp( dayInput, "wednesday" ) == 0 ) || ( strcmp( dayInput, "thursday" ) == 0 ) || ( strcmp( dayInput, "friday" ) == 0 ) || ( strcmp( dayInput, "saturday" ) == 0 ) || ( strcmp( dayInput, "sunday" ) == 0 ) )
    {
        validated = TRUE;
    }

    /*return validated*/
    return ( validated );
}

/*****************************************************************************************************
* NAME: validateTime
* PURPOSE: to validate the time
* IMPORTS: time as a string
* EXPORTS: validated as an integer
* PRE ASSERTIONS: none
* POST ASSERTIONS: whether the string is valid or not
* REMARKS:
******************************************************************************************************/

int validateTime( char* time )
{
    /*declarations*/
    int validated = FALSE, hours=0, minutes=0, valid=0;

    /*scan the string into its two seperate integers*/
    valid = sscanf( time, "%d:%d", &hours, &minutes );

    /*check the 5 cases that need to pass for the string to be valid and update validated*/
    if ( ( valid == 2 ) && ( hours >= 0 ) && ( hours <= 23 ) && ( minutes >= 0 ) && ( minutes <= 59 ) )
    {
        validated = TRUE;
    }

    /*return if the string is valid or not*/
    return ( validated );
}

