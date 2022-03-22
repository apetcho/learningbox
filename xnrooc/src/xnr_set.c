#include<stdio.h>
#include<assert.h>

#include "xnr_object.h"
#include "xnr_set.h"

const void* xnr_object;
const void* xnr_set;

#if !defined(XNR_MANY) || XNR_MANY < 1
#define XNR_MANY    10
#endif

static int xnr_heap[XNR_MANY];

//
void* xnr_new(const void* type, ...){
    int *p;
    for(p = xnr_heap+1; p< xnr_heap+XNR_MANY; ++p){
        if(!*p){break;}
    }
    assert(p < xnr_heap + XNR_MANY);
    *p = XNR_MANY;

    return p;
}
