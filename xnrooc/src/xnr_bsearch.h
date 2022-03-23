#ifndef _XNR_BSEARCH_H
#define _XNR_BSEARCH_H

#include <stddef.h>

void* xnr_bsearch(
    const void* key, void *base, size_t *nelp, size_t width,
    int (*cmp)(const void *key, const void *elt)
);

#endif
