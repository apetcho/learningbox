#include<stdarg.h>
#include<stdlib.h>
#include<assert.h>
#include<stdio.h>

#include "xnr_object.h"


//
void* xnr_new(const void *_klass, ...){
    const xnr_class *klass = _klass;
    void *ptr = calloc(1, klass->size);
    assert(ptr);
    *(const xnr_class **)ptr = klass;

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
void xnr_draw(const void *self){
    const xnr_class *const *cp = self;
    assert(self && *cp && (*cp)->draw);
    (*cp)->draw(self);
}
