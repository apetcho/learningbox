#include<stdlib.h>
#include<stdio.h>
#include<assert.h>

#include "xnr_object.h"
#include "xnr_set.h"

typedef struct xnr_set_{unsigned count; } xnr_set_t;
typedef struct xnr_object_ {
    unsigned count;
    xnr_set_t *in;
}xnr_object_t;

static const size_t _xnr_set = sizeof(xnr_set_t);
static const size_t _xnr_object = sizeof(xnr_object_t);

const void *xnr_set = &_xnr_set;
const void *xnr_object = &_xnr_object;

//
void* xnr_new(const void* type, ...){
    const size_t size = *(const size_t*)type;
    void *p = calloc(1, size);
    assert(p);
    return p;
}

//
void xnr_delete(void *item){
    free(item);
}

//
void* xnr_set_add(void* _set, const void* _element){
    xnr_set_t *set = _set;
    xnr_object_t *element = (void*)_element;

    assert(set);
    assert(element);

    if(!element->in){ element->in = set; }
    else{ assert(element->in == set); }
    ++element->count;
    ++set->count;

    return element;
}
