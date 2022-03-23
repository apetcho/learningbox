#ifndef _XNR_NAME_H
#define _XNR_NAME_H

/** xnr_name_t: maintain a table of name structures */
typedef struct xnr_name_{
    const void *type; // for dynamic linkage
    const char *name; // may be malloc-ed
    int token;
} xnr_name_t;

/** arrange for object to be found later */
void xnr_install(const void *symbol);

/** 
** find name in a table. If nothing found, enter xnr_new(xnr_variable, name)
** into table.
** 
** return associated token and pointer to structure
** 
**/
int xnr_screen(const char *name);

/** Last name found in by xnr_screen() */
extern void *xnr_symbol;

#endif
