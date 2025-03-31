/*************************************************************/
/*   File: util.h                                            */
/*   Utility function interface for the C-Minus compiler     */
/*************************************************************/

#ifndef _UTIL_H_
#define _UTIL_H_

/* Procedure printToken prints a token 
 * and its lexeme to the listing file
 */
void printToken( TokenType, const char* );

/* Function newDeclNode creates a new declaration
 * node for syntax tree construction
 */
TreePtr newDeclNode(DeclKind);

/* Function newStmtNode creates a new statement
 * node for syntax tree construction
 */
TreePtr newStmtNode(StmtKind);

/* Function newExpNode creates a new expression 
 * node for syntax tree construction
 */
TreePtr newExpNode(ExpKind);

/* Function copyString allocates and makes a new
 * copy of an existing string
 */
char * copyString( char * );

/* procedure printTree prints a syntax tree to the
 * listing file using indentation to indicate subtrees
 */
void printTree( TreePtr );

/* printTypes prints the tree with data types
 */
void printTypes( TreePtr );

#endif
