/*****************************************************************************************************
* FILE NAME: data.h
* AUTHOR: Marc Rutland Towse (18345935)
* UNIT: Unix and C Programming
* PURPOSE: declares an appropriate structure for representing a tv guide entry
* REFERENCE: none
* LAST MOD: 15th May 2018
* COMMENTS: none
*****************************************************************************************************/

#ifndef data_h
#define data_h

typedef struct {
    char* name;
    char* day;
    char* time;
} entry;

#endif
