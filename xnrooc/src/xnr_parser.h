#ifndef _XNR_PARSER_H
#define _XNR_PARSER_H

/** symbols */
typedef enum xnr_token{
    XNRTOK_NUMBER = 'n',    /* literal constant */
    XNRTOK_CONST = 'c',     /* const */ 
    XNRTOK_MATH = 'm',      /* libray function name */
    XNRTOK_VAR = 'v',       /* variable name */
    XNRTOK_LET = 'l'        /* let var = sum */
} xnr_token_t;

/** error recovery */
void xnr_error(const char *fmt, ...);

#endif
