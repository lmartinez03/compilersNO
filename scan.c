/***********************************************************/
/*    FILE: scan.c                                         */
/* PURPOSE: The scanner implementation for the C- compiler */
/* AUTHORS: Matt Dugal, Luca Martinez, Louis Sader         */
/*  COURSE: COMSC 440.01 24/SP                             */
/*    DATE: 3/19/2025                                      */
/***********************************************************/

#include "globals.h"
#include "util.h"
#include "scan.h"
#include <string.h>
#include <ctype.h>

/* States in scanner DFA */
typedef enum {
    START, INLESS, INEQ, INGREATER, INNEQ, ENTERCOMMENT,
    INCOMMENT, EXITCOMMENT, INNUM, INID, DONE
} StateType;

/* Reserved words lookup table */
static struct {
    char* str;
    TokenType tok;
} reservedWords[MAXRESERVED] = {
    {"else", ELSE}, {"if", IF}, {"int", INT},
    {"return", RETURN}, {"void", VOID}, {"while", WHILE}
};

/* Token string and position tracking */
char tokenString[MAXTOKENLEN + 1];

#define BUFLEN 256
static char lineBuf[BUFLEN]; /* Holds the current line */
static int linepos = 0;
static int bufsize = 0;
static int EOF_flag = FALSE;
static int tokenStringIndex = 0;

/* Forward declarations */
static int getNextChar(void);
static void ungetNextChar(void);
static TokenType ReservedLookupB(char* tokenStr);

/* Get next character from input buffer */
static int getNextChar(void) {
    if (!(linepos < bufsize)) {
        lineno++;
        if (fgets(lineBuf, BUFLEN-1, source)) {
            if (EchoSource) fprintf(listing, "%4d: %s", lineno, lineBuf);
            bufsize = strlen(lineBuf);
            linepos = 0;
            return lineBuf[linepos++];
        } else {
            EOF_flag = TRUE;
            return EOF;
        }
    }
    return lineBuf[linepos++];
}

/* Push back last character */
static void ungetNextChar(void) {
    if (!EOF_flag) linepos--;
}

/* Binary search for reserved words */
static TokenType ReservedLookupB(char* tokenStr) {
    int low = 0, high = MAXRESERVED - 1;
    while (low <= high) {
        int mid = (low + high) / 2;
        int cmp = strcmp(tokenStr, reservedWords[mid].str);
        if (cmp < 0) high = mid - 1;
        else if (cmp > 0) low = mid + 1;
        else return reservedWords[mid].tok;
    }
    return ID;
}

/* Main scanner function */
TokenType getToken(void) {
    StateType state = START;
    TokenType currentToken = ERROR;
    int c;
    tokenStringIndex = 0;
    tokenString[0] = '\0';

    while (state != DONE) {
        c = getNextChar();
        int save = TRUE;

        switch (state) {
            case START:
                if (isdigit(c)) {
                    state = INNUM;
                } else if (isalpha(c)) {
                    state = INID;
                } else if (c == '<') {
                    state = INLESS;
                    save = FALSE;
                } else if (c == '>') {
                    state = INGREATER;
                    save = FALSE;
                } else if (c == '=') {
                    state = INEQ;
                    save = FALSE;
                } else if (c == '!') {
                    state = INNEQ;
                    save = FALSE;
                } else if (c == '/') {
                    int next = getNextChar();
                    if (next == '*') {
                        state = ENTERCOMMENT;
                        save = FALSE;
                    } else {
                        ungetNextChar();
                        currentToken = OVER;
                        state = DONE;
                    }
                } else if (isspace(c)) {
                    save = FALSE;
                } else {
                    state = DONE;
                    switch (c) {
                        case '+': currentToken = PLUS; break;
                        case '-': currentToken = MINUS; break;
                        case '*': currentToken = TIMES; break;
                        case ';': currentToken = SEMI; break;
                        case ',': currentToken = COMMA; break;
                        case '(': currentToken = LPAREN; break;
                        case ')': currentToken = RPAREN; break;
                        case '[': currentToken = LBRACKET; break;
                        case ']': currentToken = RBRACKET; break;
                        case '{': currentToken = LCURLY; break;
                        case '}': currentToken = RCURLY; break;
                        case EOF: currentToken = ENDFILE; break;
                        default: currentToken = ERROR; break;
                    }
                }
                break;

            case INLESS:
                state = DONE;
                if (c == '=') currentToken = LE;
                else {
                    ungetNextChar();
                    currentToken = LT;
                }
                break;

            case INEQ:
                state = DONE;
                if (c == '=') currentToken = EQ;
                else {
                    ungetNextChar();
                    currentToken = ASSIGN;
                }
                break;

            case INGREATER:
                state = DONE;
                if (c == '=') currentToken = GE;
                else {
                    ungetNextChar();
                    currentToken = GT;
                }
                break;

            case INNEQ:
                state = DONE;
                if (c == '=') currentToken = NE;
                else currentToken = ERROR;
                break;

            case INNUM:
                if (!isdigit(c)) {
                    ungetNextChar();
                    save = FALSE;
                    state = DONE;
                    currentToken = NUM;
                } 
                break;

            case INID:
                if (!isalnum(c)) {
                    ungetNextChar();
                    save = FALSE;
                    state = DONE;
                    currentToken = ID;
                } 
                break;

            case ENTERCOMMENT:
                save = FALSE;
                state = INCOMMENT;
                break;

            case INCOMMENT:
                save = FALSE;
                if (c == '*') state = EXITCOMMENT;
                else if (c == EOF) {
                    currentToken = ERROR;
                    state = DONE;
                }
                break;

            case EXITCOMMENT:
                save = FALSE;
                if (c == '/') state = START;
                else if (c == '*') state = EXITCOMMENT;
                else state = INCOMMENT;
                break;
            case DONE:
            default:
                fprintf(listing, "Scanner Bug: state= %d\n", state);
                state = DONE;
                currentToken = ERROR;
                break;
        }

        if (save && tokenStringIndex < MAXTOKENLEN)
            tokenString[tokenStringIndex++] = c;

        if (state == DONE) {
            tokenString[tokenStringIndex] = '\0';
            if (currentToken == ID)
                currentToken = ReservedLookupB(tokenString);
        }
    }

    if (TraceScan) {
        fprintf(listing, "\t%d: ", lineno);
        printToken(currentToken, tokenString);
    }

    return currentToken;
}
