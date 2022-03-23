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

//
static xnr_name_t **_xnr_search(const char **name){
    static const xnr_name_t **names; // dynamic tables
    static size_t used;
    static size_t max;

    if(used >= max){
        names = names ?
            realloc(names, (max *= 2)*sizeof(*names))
            : malloc((max = XNR_NAMES)*sizeof(*names));

        assert(names);
    }

    return xnr_bsearch(name, names, &used, sizeof(*names), _xnr_cmp);
}


void xnr_install(const void *np){}

void *xnr_symbol;

int xnr_screen(const char *name){}

