
/*************************************************************/
/*   File: analyze.h                                         */
/*   Semantic analyzer interface for C-Minus compiler        */
/*************************************************************/

#ifndef _ANALYZE_H_
#define _ANALYZE_H_


/* Function buildSymtab constructs the symbol
 * table by a mainly preorder traversal of the syntax tree
 */
void buildSymtab(TreePtr);

/* Procedure typeCheck performs type checking
 * by a mainly postorder syntax tree traversal
 */
void typeCheck(TreePtr);

#endif
