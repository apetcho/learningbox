#ifndef _XNR_PARSER_H
#define _XNR_PARSER_H

/** symbols */
typedef enum xnr_token{ XNR_NUMBER = 'n'} xnr_token_t;
/** error recovery */
void xnr_error(const char *fmt, ...);

#endif
