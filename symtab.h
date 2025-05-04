
/*************************************************************/
/*   File: symtab.h                                          */
/*   Symbol table interface for the C-Minus compiler         */
/*   (allows only one symbol table)                          */
/*********************************************************** */


#include "globals.h"
#ifndef _SYMTAB_H_
#define _SYMTAB_H_


/* Procedure st_enterScope starts a new scope
 * returns 0 if memory allocation fails, else 1
 */
int st_enterScope(void);

/* Procedure st_exitScope removes all declarations
 * in the current scope
 */
void st_exitScope(void);

/* Procedure st_insert inserts def nodes from
 * from the syntax tree into the symbol table
 * returns 0 if memory allocation fails, else 1
 */
int st_insert( TreePtr );

/* Function st_lookup returns the defnode
 * of a variable, parameter, or function,
 * or NULL if not found
 */
TreePtr st_lookup ( char * name );

#endif
