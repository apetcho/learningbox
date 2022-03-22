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

//
void xnr_delete(void* item){
    int *xnr_item = item;

    if(xnr_item){
        assert(xnr_item > xnr_heap && xnr_item < xnr_heap + XNR_MANY);
        *xnr_item = 0;
    }
}

//
void* xnr_set_add(void *_set, const void* _element){
    int *set = _set;
    const int* element = _element;

    assert(set > xnr_heap && set < xnr_heap + XNR_MANY);
    assert(*set == XNR_MANY);
    assert(element > xnr_heap && element < xnr_heap + XNR_MANY);

    if(*element == XNR_MANY){
        *(int*)element = set - xnr_heap;
    }else{
        assert(*element == set - xnr_heap);
    }

    return (void*)element;
}

//
void* xnr_set_find(const void* _set, const void* _element){
    const int *set = _set;
    const int *element = _element;

    assert(set > xnr_heap && set < xnr_heap + XNR_MANY);
    assert(*set == XNR_MANY);
    assert(element > xnr_heap && element < xnr_heap + XNR_MANY);
    assert(*element);

    return *element == (set - xnr_heap) ? (void*)element : 0;
}

int xnr_set_contains(const void* _set, const void* _element){
    return xnr_set_find(_set, _element) != 0;
}

//
void* xnr_set_drop(void* _set, const void* _element){
    int *element = xnr_set_find(_set, _element);
    if(element){
        *element = XNR_MANY;
    }

    return element;
}

//
int xnr_differ(const void* lhs, const void* rhs){
    return lhs != rhs;
}
