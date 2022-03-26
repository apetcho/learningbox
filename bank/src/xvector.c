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
    ItemCopyFn copyfn;
};

/** Initialize a vector with a specified capacity and itemsize */
XVector_t* vector_malloc(
    ItemAllocator allocate,
    ItemDeallocator deallocate,
    ItemCopyFn copyfn,
    size_t capacity, size_t itemsize
){
    XVector_t *vec = (XVector_t*)malloc(sizeof(*vec));
    if(vec){
        size_t cap = (capacity <= 1) ? DEFAULT_CAPACITY : capacity;
        vec->data = allocate(cap * itemsize);
        vec->capacity = (vec->data == 0)? 0: cap;
        vec->size = 0;
        vec->itemsize = itemsize;
        vec->allocate = allocate;
        vec->deallocate = deallocate;
        vec->copyfn = copyfn;
    }

    return vec;
}

/** Realse memory owned by xvector */
void vector_free(XVector_t *vec){
    for(size_t i=(vec->size-1); i >0; i--){
        vec->deallocate(vec->data[i]);
    }
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
        void *data = vec->allocate(newsize*vec->itemsize); 
        if(data == NULL){
            return -1;
        }
        vec->capacity = newsize;
        ItemCopyFn copyfn = vec->copyfn;
        ItemDeallocator deallocate = vec->deallocate;
        for(i=0; i < vec->size; i++){
            copyfn(data[i], vec->data[i]);
            deallocate(vec->data[i]);
        }
        vec->data = data;
    }

    // add the item now
    vec->copyfn(vec->data[vec->size], item);
    return vec->size++;
}

/**
 * @brief Return item from back of vector and remove it from the vector.
 * 
 * @param vec   Vector collection
 * @param item  Item returned from the back of vec
 */
void vector_pop_back(XVector_t *vec, void *item){
    assert(vec->size > 0);
    ItemDeallocator delfn = vec->deallocate;
    ItemCopyFn copyfn = vec->copyfn;
    size_t index = vec->size - 1;
    copyfn(item, vec->data[index]);
    delfn(vec->data[index]);

    --vec->size;
}

/**
 * @brief Return a copy of the element at the specified index
 * 
 * @param vec 
 * @param index 
 * @return void* 
 */
void* vector_get_item(XVector_t *vec, size_t index){
    assert(index >= 0 && index < vec->size);
    void *item;
    vec->copyfn(item, vec->data[index]);
    return item;
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

/**
 * @brief Set vector size.
 * 
 * @param vec 
 * @param size 
 * @return int 0 if successful, otherwise -1
 */
int vector_set_size(XVector_t *vec, size_t size){
    if(size > vec->capacity){
        void *data = vec->allocate(size*vec->itemsize);
        if(data == NULL){ return -1; }
        for(size_t i = 0; i < vec->size; i++){ /* copy all item already stored*/
            vec->copyfn(data[i], vec->data[i]);
        }
        for(size_t i=0; i < vec->size; i++){
            vec->deallocate(vec->data[i]);
        }
        
        vec->capacity = size; /* new capacity */
        vec->data = data;
    }else if(size < vec->size && size > 0){
        void *data = vec->allocate(size*vec->itemsize);
        if(data == NULL){ return -1; }
        for(size_t i = 0; i < size; i++){ /* copy only the first 'size' items*/
            vec->copyfn(data[i], vec->data[i]);
        }
        for(size_t i=0; i < vec->size; i++){
            vec->deallocate(vec->data[i]);
        }
        
        //vec->capacity = size;
        vec->data = data;
    }else{ /* negative size was given. This is an error */
        return -1;
    }

    vec->size = size;
    return 0;
}
