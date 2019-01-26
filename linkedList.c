/*****************************************************************************************************
* FILE NAME: linkedList.c
* AUTHOR: Marc Rutland Towse (18345935)
* UNIT: Unix and C Programming
* PURPOSE: contains all necessary functions for creating, destroying, manipulating, and accessing 
*       a linked list. 
* REFERENCE: DSA lecture notes + Laboratory work
* LAST MOD: 27th May 2018
* COMMENTS: none
*****************************************************************************************************/

/*includes*/
#include <stdio.h>
#include <stdlib.h>
#include "linkedList.h"
#include "boolean.h"
/*****************************************************************************************************
* NAME: insertFirst
* PURPOSE: to insert a node at the start of a list (the head)
* IMPORTS: Linkedlist pointer list, and input as a void pointer
* EXPORTS: none
* PRE ASSERTIONS: the input is whats needed to go in the list
* POST ASSERTIONS: the node created and inserted into the front of the list
* REMARKS: none
******************************************************************************************************/

void insertFirst( LinkedList* list, void* input )
{
    /*using calloc to create and initialise to null the new node*/
    LLNode* newNode = ( LLNode* )calloc( 1, sizeof ( LLNode ) );
    /*placing the input into the data*/
    newNode -> data = input;

    /*if the list is empty newNode becomes head and tail*/
    if ( !isEmpty( list ) == 0 )
    {
        list -> head = newNode;
        list -> tail = newNode;
    }
    /*insert before the head*/
    else
    {
        newNode -> next = list -> head;
        list -> head -> prev = newNode;
        list -> head = newNode;
    }

    ( list->count++ );
}

/*****************************************************************************************************
* NAME: insertLast
* PURPOSE: to insert a nod at the end of a list (the tail)
* IMPORTS: Linkedlist pointer list, input as a void pointer
* EXPORTS: none
* PRE ASSERTIONS: the input is whats needed to go in the list
* POST ASSERTIONS: the node created and inserted into the back of the list
* REMARKS: none
******************************************************************************************************/

void insertLast( LinkedList* list, void* input )
{
    /*using calloc to create and initialise to null the new node*/
    LLNode* newNode = ( LLNode* )calloc( 1, sizeof ( LLNode ) );
    /*placeing the input into the data*/
    newNode -> data = input;

    /*if the list is empty the newNode becomes head and tail*/
    if ( !isEmpty( list ) == 0 )
    {
        list -> head = newNode;
        list -> tail = newNode;
    }
    /*insert after the tail*/
    else
    {
        newNode -> prev = list -> tail;
        list -> tail -> next = newNode;
        list -> tail = newNode;
    }

    ( list->count++ );
}

/*****************************************************************************************************
* NAME: deleteFirst
* PURPOSE: to delete the first node in the list
* IMPORTS: LinkedList pointer list
* EXPORTS: none
* PRE ASSERTIONS: none
* POST ASSERTIONS: the first node is deleted or an error for an empty list displayed
* REMARKS:
******************************************************************************************************/

void deleteFirst( LinkedList* list )
{
    /*throw an error if the list is empty*/
    if ( !isEmpty( list ) == 0 )
    {
        fprintf( stderr, "Attempted to delete element from empty list" );
    }
    else
    {
        /*if theres only one node delete it and NULL the list fields*/
        if ( list -> head -> next == NULL )
        {
            free( list -> head );
            list -> head = NULL;
            list -> tail = NULL;
        }
        /*else remove the head and add a new head value*/
        else
        {
            LLNode* temp = list -> head;
            list -> head = list -> head -> next;
            free( temp );
        }

        (list->count)--;
    }
}

/*****************************************************************************************************
* NAME: deleteLast
* PURPOSE: to delete the last node in the list
* IMPORTS: LinkedList pointer list
* EXPORTS: none
* PRE ASSERTIONS: none
* POST ASSERTIONS: the last node is deleted or an error for an empty list displayed
* REMARKS: none
******************************************************************************************************/

void deleteLast( LinkedList* list )
{
    /*throw an error if the list is empty*/
    if ( !isEmpty( list ) == 0 )
    {
        fprintf( stderr, "Attempted to delete element from empty list" );
    }
    else
    {
        /*if theres onle one node delete it and NULL the list fields*/
        if ( list -> tail -> prev == NULL )
        {
            free( list -> tail );
            list -> tail = NULL;
            list -> head = NULL;
        }
        /*else remove the tail and add a new tail value*/
        else
        {
            LLNode* temp = list -> tail;
            list -> head = list -> tail -> prev;
            free( temp );
        }

        (list->count)--;
    }
}

/*****************************************************************************************************
* NAME: deleteCurrent
* PURPOSE: to delete the current node from the list
* IMPORTS: LLNode pointer current
* EXPORTS: none
* PRE ASSERTIONS: none
* POST ASSERTIONS: the node is deleted or an error is thrown
* REMARKS: none
******************************************************************************************************/

void deleteCurrent( LLNode* current, LinkedList* list )
{
    /*if the node doesn't exist throw an error*/
    if ( current == NULL )
    {
        fprintf( stderr, "Attempted to delete non existant node" );
    }
    else
    {
        if ( current -> next == NULL )
        {
            /*only one node in list*/
            if ( current -> prev == NULL )
            {
                free( current );
                list -> head = NULL;
                list -> tail = NULL;
            }
            /*delete the tail*/
            else
            {
                deleteLast( list );
            }
        }
        else
        {
            /*delete the head*/
            if ( current -> prev == NULL )
            {
                deleteFirst( list );   
            }
            /*delete a node from inside the list*/
            else
            {
                current -> next -> prev = current -> prev;
                current -> prev -> next = current -> next;
                free( current );
            }
        }

        (list->count)--;
    }
}

/*****************************************************************************************************
* NAME: insertAfter
* PURPOSE: to insert a node after a selected node
* IMPORTS: LLNode pointer current, void pointer for the data, linkedList poitner list
* EXPORTS: none
* PRE ASSERTIONS: the data is whats intended to be inserted
* POST ASSERTIONS: the node has been created and inserted after the current
* REMARKS: none
******************************************************************************************************/

void insertAfter( LLNode* current, void* data, LinkedList* list )
{
    /*print an error if no node given*/
    if ( current == NULL )
    {
        fprintf( stderr, "attempted to insert after non existant node" );
    }    
    else
    {
        /*initialise new node with the data*/
        LLNode* newNode = ( LLNode* )calloc( 1, sizeof ( LLNode ) );
        newNode -> data = data;

        /*current node is tail*/
        if ( current -> next == NULL )
        {
            newNode -> next = NULL;
            newNode -> prev = current;
            current -> next = newNode;
            list -> tail = newNode;
        }
        /*insert new node after the current and rearange list accordingly*/
        else
        {
            current -> next -> prev = newNode;
            newNode -> next = current -> next;
            current -> next = newNode;
            newNode -> prev = current;
        }

        ( list->count++ );
    }
}
/*****************************************************************************************************
* NAME: insertBefore
* PURPOSE: to inser a node before the selected node
* IMPORTS: LLNode pointer current, void pointer for the data, linkedLIst pointer list
* EXPORTS: none
* PRE ASSERTIONS: the data is whats intended to be inserted
* POST ASSERTIONS: the node has been created and inserted before the current
* REMARKS: none
******************************************************************************************************/

void insertBefore( LLNode* current, void* data, LinkedList* list )
{
    /*print an error if no node given*/
    if ( current == NULL )
    {
        fprintf( stderr, "attempted to insert before non existant node" );
    }    
    else
    {
        /*initialise newNode with the data*/
        LLNode* newNode = ( LLNode* )calloc( 1, sizeof ( LLNode ) );
        newNode -> data = data;

        /*current node is head*/
        if ( current -> prev == NULL )
        {
            newNode -> prev = NULL;
            newNode -> next = current;
            current -> prev = newNode;
            list -> head = newNode;
        }
        /*insert new node after the current and rearange list accordingly*/
        else
        {
            current -> prev -> next = newNode;
            newNode -> prev = current -> prev;
            current -> prev = newNode;
            newNode -> next = current;
        }

        ( list->count++ );
    }
}

/*****************************************************************************************************
* NAME: freeList
* PURPOSE: to free the list after its not needed
* IMPORTS: LinkedList pointer list
* EXPORTS: none
* PRE ASSERTIONS: none
* POST ASSERTIONS: the list is now free'd
* REMARKS: none
******************************************************************************************************/

void freeList( LinkedList* list )
{
    /*if isn't empty then free all nodes before the list*/
    if( !isEmpty( list ) )
    {
        LLNode* node,* nextNode;

        node = list -> head;
        /*iterate the list until no nodes are left*/
        while ( node != NULL )
        {
            nextNode = node -> next;
            free( node );
            node = nextNode;
            (list->count)--;
        }
        free( list );
    }
    /*else just free the list*/
    else
    {
        free( list );
    }
}
/*****************************************************************************************************
* NAME: isEmpty
* PURPOSE: to check if the list is empty and return with a boolean
* IMPORTS: LinkedList pointer list
* EXPORTS: integer for TRUE and FALSE
* PRE ASSERTIONS: none
* POST ASSERTIONS: if the list is empty
* REMARKS: none
******************************************************************************************************/

int isEmpty( LinkedList* list )
{
    /*set to not empty*/
    int empty = FALSE;

    /*if empty then set to empty*/
    if ( list -> head == NULL )
    {
        empty = TRUE;
    }

    /*return empty*/
    return ( empty );
}

