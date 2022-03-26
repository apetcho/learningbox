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

/** Realse memory owned by xvector */
void vector_free(XVector_t *vec){
    vec->deallocate(vec->data);
    free(vec);
}

/**
 * @brief Add item to back of vector
 * 
 * 
 * @param vec   Vecotr collection 
 * @param item  Item to add to the vector collection
 * @return int  Index of the new element if successful, otherwise -1
 */
int vector_push_back(XVector_t *vec, const void *item){
    if(vec->size == vec->capacity){// not enough memory, re-adjust memory size
        size_t nsolts = (size_t)(vec->capacity * GROWTH_RATE + 1.0);
        size_t newsize = (vec->capacity == 0)? DEFAULT_CAPACITY : nsolts;
        void *data = realloc(vec->data, newsize*vec->itemsize);
        if(data == NULL){
            return -1;
        }
        vec->capacity = newsize;
        vec->data = data;
    }
    // add the item now
    memcpy((char*)vec->data + (vec->itemsize*vec->size), item, vec->itemsize);
    return vec->size++;
}

/**
 * @brief Return item from back of vector and remove it from the vector.
 * 
 * @param vec   Vector collection
 * @param item  Item returned from the back of vec
 */
void vector_push_back(XVector_t *vec, void *item){
    assert(vec->size > 0);
    --vec->size;
    memcpy(item, (char*)vec->data + (vec->itemsize*vec->size), vec->itemsize);
}

/**
 * @brief Return pointer to the element at the specified index
 * 
 * @param vec 
 * @param index 
 * @return void* 
 */
void* vector_get_item(XVector_t *vec, size_t index){
    assert(index >= 0 && index < vec->size);
    return (char *)vec->data + index * vec->itemsize;
}

/**
 * @brief Return pointer to beginning of array
 * 
 * @param vec 
 * @return void* 
 */
void* vector_get_begin(XVector_t *vec){
    return vec->data;
}

/**
 * @brief Return pointer to one-past-end of array
 * 
 * @param vec 
 * @return void* 
 */
void* vector_get_end(XVector_t *vec){
    return (char*)vec->data + (vec->size * vec->itemsize);
}

// ---
size_t vector_get_itemsize(const XVector_t *vec){
    return vec->itemsize;
}

// ---
size_t vector_get_size(const XVector_t *vec){
    return vec->size;
}

// ---
size_t vector_get_capacity(const XVector_t *vec){
    return vec->capacity;
}
