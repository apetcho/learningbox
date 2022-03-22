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

//
void* xnr_set_find(const void* _set, const void* _element){
    const xnr_object_t *element = _element;

    assert(_set);
    assert(element);

    return element->in == _set ? (void*)element : 0;
}

//
int xnr_set_contains(const void* _set, const void* _element){
    return xnr_set_find(_set, _element) != 0;
}
