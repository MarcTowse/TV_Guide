/*****************************************************************************************************
* FILE NAME: linkedList.h
* AUTHOR: Marc Rutland Towse (18345935)
* UNIT: Unix and C Programming
* PURPOSE: to provide the forward declarations of linkedList.c and the structures needed for a list
* REFERENCE: DSA Lecture notes + laboratory work
* LAST MOD: 27th May 2018
* COMMENTS: none
*****************************************************************************************************/

#ifndef linkedList_h
#define linkedList_h



/*structure for the node*/
typedef struct LLNode{
    void* data;
    struct LLNode* next;
    struct LLNode* prev;
} LLNode;

/*structure for the list*/
typedef struct {
    struct LLNode* head;
    struct LLNode* tail;
    int count;
} LinkedList;

void insertFirst(LinkedList* list, void* input);
void insertLast(LinkedList* list, void* input);
void deleteFirst(LinkedList* list);
void deleteLast(LinkedList* list);
void insertBefore( LLNode* current, void* data, LinkedList* list );
void insertAfter( LLNode* current, void* data, LinkedList* list );
void deleteCurrent( LLNode* current, LinkedList* list );
void freeList(LinkedList* list);
int isEmpty(LinkedList* list);

#endif
