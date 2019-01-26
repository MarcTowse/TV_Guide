/*****************************************************************************************************
* FILE NAME: tvguide.c
* AUTHOR: Marc Rutland Towse (18345935)
* UNIT: Unix and C Programming
* PURPOSE: contains the main function, is the initial file to open when running the program
* REFERENCE: www.tutorialspoint.com/c_standard_library/c_function_qsort.htm
* LAST MOD: 27th May 2018
* COMMENTS: none
*****************************************************************************************************/

/*included header files*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "data.h"
#include "interface.h"
#include "linkedList.h"
#include "tvguide.h"
#include "fileIO.h"
#include "boolean.h"
#include "comparison.h"

/********************************************************************************************************
 * NAME: main
 * PURPOSE: invokes other functions and is the initial function called when the program starts
 * IMPORTS: Integer argc, String argv[]
 * EXPORTS: Integer value 0
 * PRE ASSERTIONS: none
 * POST ASSERTIONS: an error will be displayed out the stderror channel or the contents of an array will 
 * be displayed to stdout and an output file.
 ********************************************************************************************************/

int main ( int argc, char* argv[] ) 
{
    /*check for correct number of command line arguments*/
    if ( argc == 3 ) 
    {
        /*declare needed variables*/
        int arrayLength, n=1, errorRead = FALSE,  linesRead=0, total;
        char day[11];
        char choice[6];
        entry* array;
        LinkedList* list =  ( LinkedList* )calloc( n, sizeof ( LinkedList ) );
    
        /*read in the data and input the user selects*/
        acceptInput ( day, choice ); 
        fileRead ( list, argv[1], &errorRead, &linesRead );
        
        /*only run the program if there is no errors, otherwise abort*/
        if ( errorRead != TRUE )
        {
            /*array creation + length achknowledgment*/
            array = calloc( list->count, sizeof ( entry ) );
            arrayLength = list->count;
            total =  list->count;

            /*call the functions which mutate the array/list*/
            convertToArray( list, array );
            sort( array, &arrayLength, choice );
            filter( array, &arrayLength, day );
    
            /*call the output functions*/
            printTerminal( array, &arrayLength );
            fileWrite( array, &arrayLength, argv[2] );

            /*free all allocated memory that hasn't been free'd yet*/
            freeAll( list, total );
            free( array );
        }
        else
        {
            /*call a function that handles the error output*/
            printReadError( linesRead );
        }
    }
    else
    {
        /*error message for incorrect number of command line arguments*/
        fprintf ( stderr, "Incorrect number of command paramaters" ) ;
    }

    return ( 0 ) ;
}

/*******************************************************************************************************
 * NAME: convertToArray
 * PURPOSE: convert a linked list to an array
 * IMPORTS: LinkedList pointer list, entry pointer array
 * EXPORTS: None
 * PRE ASSERTIONS: list contents is valid and matches array type plus size
 * POST ASSERTIONS: list contents is now in an array with list.head = array[0]
 *******************************************************************************************************/

void convertToArray( LinkedList* list, entry* array ) 
{
    int i;
    /*creates a starting point to iterate the list with*/
    LLNode* current = list->head;    

    /*for loop iterates the array for every list value*/
    for ( i=0; i<list->count; i++ ) 
    {
        /*array data = list data as they both iterate through*/
        array[i] = *( entry* )current->data;
        /*this iterates through the list when combined with the for loop*/
        current = current->next;
    }
}

/******************************************************************************************************
 * NAME: filter
 * PURPOSE: filter the unwanted entries out of the array
 * IMPORTS: entry pointer array, an integer for array length, the selected day as a string
 * EXPORTS: none
 * PRE ASSERTIONS: the array has been filled with valid data, correct array length proivded and the 
 *      selected day is valid
 * POST ASSERTIONS: the array and its new array length are valid and filtered
 * REMARKS: function doesn't actaully remove unwanted values but instead moves wanted values to the
 *      front of the array and then changes the length to "cut off" unwanted values
 *****************************************************************************************************/

void filter( entry* array, int* arrayLength, char* day )
{
    /*declarations*/
    int i, match=0;
    
    /*iterate through the whole array*/
    for ( i=0; i<*arrayLength; i++ )
    {
        /*if theres a match with data and the wanted day execute the if statement*/
        if ( strcmp( array[i].day, day ) == 0 )
        {
            /*wanted value gets pushed into a earlier spot*/
            array[match] = array[i];
            /*the new spot to insert matching data is incremented*/
            match++;
        }
    }
    /*the unwanted values are cut off*/
    *arrayLength = match;
}

/*****************************************************************************************************
 * NAME: sort
 * PURPOSE: sort the array contents how the user chooses, alphabetically or chronologically
 * IMPORTS: entry pointer array, an integer for array length and user choice as a string
 * EXPORTS: none
 * PRE ASSERTIONS: the array has been filled with valid data, correct array length provided and the
 *      selected choice is valid
 * POST ASSERTIONS: the array will now be sorted
 * REMARKS: array is sorted using qsort
 *****************************************************************************************************/

void sort( entry* array, int* arrayLength, char* choice )
{
    /*if the choice is name call use compareName otherwise use compareTime*/
    if ( strcmp( choice, "name" )==0 )
    {
        qsort( array, *arrayLength, sizeof ( entry ), compareName );
    }
    else
    {
        qsort( array, *arrayLength, sizeof ( entry ), compareTime );
    }
}

/****************************************************************************************************
 * NAME: freeAll
 * PURPOSE: free the list and its data
 * IMPORTS: the list
 * EXPORTS: none
 * PRE ASSERTIONS: none
 * POST ASSERTIONS: the provided list is now free
 * REMARKS:
 ***************************************************************************************************/

void freeAll( LinkedList* list, int total )
{
    int i;

    /*iterate through the list*/
    for ( i=0; i<total; i++ ) 
    {
        /*free the data then before deleteing the node holding it*/
        free( ( *( entry* )list->head->data ).name );
        free( ( *( entry* )list->head->data ).time );
        free( ( *( entry* )list->head->data ).day );
        free( ( entry* )list->head->data );
        deleteFirst( list );
    }
    /*free the list itself*/
    freeList( list );
}

/****************************************************
 * NAME: printReadError
 * PURPOSE: print out the correct error message
 * IMPORTS: an integer for the number of lines read
 * EXPORTS: none
 * PRE ASSERTIONS: linesRead is correct
 * POST ASSERTIONS: the error message has been printed
 * REMARKS:
 ***************************************************/

void printReadError( int linesRead )
{
    /*if 1 is returned it means the error happened on the first scan*/
    if ( linesRead == 1 )
    {
        fprintf( stderr, "-----------------------------------------------\n" );
        fprintf( stderr, "   Program Abort: Data corrupted on line %d\n", linesRead );
        fprintf( stderr, "   Possible empty data file \n" );
        fprintf( stderr, "-----------------------------------------------\n" );
    }
    /*print corrupted data plus the scanned line*/
    else
    {
        fprintf( stderr, "-----------------------------------------------\n" );
        fprintf( stderr, "   Program Abort: Data corrupted on line %d\n", linesRead );
        fprintf( stderr, "-----------------------------------------------\n" );
    }
}
