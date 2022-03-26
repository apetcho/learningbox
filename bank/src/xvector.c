#include<stdlib.h>
#include<string.h>
#include<assert.h>
#include<errno.h>
#include<stdio.h>

#include "xvector.h"

static const int DEFAULT_CAPACITY = 2;
static const double GROWTH_RATE = 1.5;

struct XVector_{
    void *data;
    size_t capacity;
    size_t size;
    size_t itemsize;
    ItemAllocator allocate;
    ItemDeallocator deallocate;
};

/** Initialize a vector with a specified capacity and itemsize */
XVector_t* vector_malloc(
    ItemAllocator allocate, ItemDeallocator deallocate,
    size_t capacity, size_t itemsize
){
    XVector_t *vec = (XVector_t*)malloc(sizeof(*vec));
    if(vec){
        size_t cap = (capacity == 1) ? DEFAULT_CAPACITY : capacity;
        vec->data = allocate(cap * itemsize);
        vec->capacity = (vec->data == 0)? 0: cap;
        vec->size = 0;
        vec->itemsize = itemsize;
        vec->allocate = allocate;
        vec->deallocate = deallocate;
    }

    return vec;
}
