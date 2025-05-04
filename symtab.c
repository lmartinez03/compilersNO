
/*************************************************************/
/*   File: symtab.c                                          */
/*   Symbol table implementation for the C-Minus compiler    */
/*   (allows only one symbol table)                          */
/*                                                           */
/*   This file needs to be completed as part of your project4*/
/*************************************************************/

#include "symtab.h"


/* SIZE is the size of each hash table */
#define SIZE 211

/* SHIFT is the power of two used as multiplier
   in hash function  */
#define SHIFT 4

/* the hash function */
static int hash ( char * key )
{ int temp = 0;
    //(1): add code here to complete the implementation of the hash function

  return temp;
}

/* The record in the bucket lists for
 * each defnode
 */
typedef struct BucketListRec
   { TreePtr defnode;
     struct BucketListRec * next;
   } * BucketList;

/* each hash table */
typedef BucketList Table[SIZE];

/* the linked list of tables */
typedef struct TableListRec
   { Table t;
     struct TableListRec * next;
   } * TableList;

/* The actual symbol table */
static TableList symTab = NULL; /* starts out empty */

/* Procedure st_enterScope starts a new scope
 * returns 0 if memory allocation fails, else 1
 */
int st_enterScope(void)
{ TableList tempTab = (TableList) malloc(sizeof(struct TableListRec));
  int i;
  if (!tempTab) return 0; /* memory allocation error */
  for (i=0;i<SIZE;i++) tempTab->t[i] = NULL;
  tempTab->next = symTab;
  symTab = tempTab;
  return 1;
} /* st_enterScope */

/* Procedure st_exitScope removes all declarations
 * in the current scope
 */
void st_exitScope(void)
{ 

	//(2): Add code to handle the case when a scope needs to be deleted
}

/* Procedure st_insert inserts def nodes from
 * from the syntax tree into the symbol table
 * returns 0 if memory allocation fails, else 1
 */
int st_insert( TreePtr t)
{ int h = hash(t->attr.name);
  BucketList l;
  if (!symTab) st_enterScope();
  if (!symTab) return 0; /* memory allocation error */
  l = (BucketList) malloc(sizeof(struct BucketListRec));
  if (!l) return 0; /* memory allocation error */
  l->defnode = t;
  l->next = symTab->t[h];
  symTab->t[h] = l;
  return 1;
}

TreePtr st_lookup ( char * name )
{ 

  //(3) Add code to handle the case of lookup process
  
  //3-1 calc the hash value of the name 
  //3-2 create a temp variable (TableList) and use it to scan through the whole table looking for a match 
  //3-3 while loop to go through the table
  //    for each iteration of the loop
  //       find each hash table content - should be a BucketList
  //       compare the name of the content with the name looking for (defnode->arrt.name)
  //       if name is found, return the defnode of the current BucketList
  //               else move on to the next table content
  //3-4 return NULL if not found; 

}  /* st_lookup */

