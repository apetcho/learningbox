#include<stdarg.h>
#include<stdlib.h>
#include<assert.h>
#include<stdio.h>

#include "xnr_object.h"
struct xnr_class{
    size_t size;
    void* (*ctor)(void *self, va_list *args);
    void* (*dtor)(void *self);
    void* (*clone)(const void *self);
    int (*differ)(const void *self, const void *other);
};

//
void* xnr_new(const void *_klass, ...){
    const xnr_class *klass = _klass;
    void *ptr = calloc(1, klass->size);
    assert(ptr);
    *(xnr_class **)ptr = klass;

    if(klass->ctor){
        va_list args;
        va_start(args, _klass);
        ptr = klass->ctor(ptr, &args);
        va_end(args);
    }

    return ptr;
}

//
void xnr_delete(void *self){
    const xnr_class **cp = self;
    if(self && *cp && (*cp)->dtor){
        self = (*cp)->dtor(self);
    }
    free(self);
}

//
void* xnr_clone(const void *self){
    const xnr_class *const *cp = self;
    assert(self && *cp && (*cp)->clone);
    return (*cp)->clone(self);
}

//
int xnr_differ(const void *self, const void *other){
    const xnr_class *const *cp = self;
    assert(self && *cp && (*cp)->differ);
    return (*cp)->differ(self, other);
}

//
size_t xnr_sizeof(const void *self){
    const xnr_class *const *cp = self;
    assert(self && *cp);
    return (*cp)->size;
}

size_t xnr_len(const void *self){
    const xnr_class *const *cp = self;
    assert(self && *cp);
    return (*cp)->size;
}
