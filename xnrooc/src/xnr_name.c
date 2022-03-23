#include<stdlib.h>
#include<stdarg.h>
#include<string.h>
#include<assert.h>

#include "xnr_bsearch.h"
#include "xnr_parser.h"
#include "xnr_value.h"
#include "xnr_name.h"
#include "xnr_variable.h"

#ifndef XNR_NAMES   /* tunable: initial size of symbol table */
#define XNR_NAMES   4
#endif

//
static int _xnr_cmp(const void *_key, const void *_elt){
    const char *const *key = _key;
    const xnr_name_t *const *elt = _elt;
    return strcmp(*key, (*elt)->name);
}

static xnr_name_t **_xnr_search(const char **name){}


void xnr_install(const void *np){}

void *xnr_symbol;

int xnr_screen(const char *name){}

