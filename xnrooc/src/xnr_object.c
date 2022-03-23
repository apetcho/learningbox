#include<stdarg.h>
#include<stdlib.h>
#include<assert.h>
#include<stdio.h>
#include<string.h>

#include "xnr_object.h"

// -- object --
//! @todo
static void* _xnr_object_ctor(void *_self, va_list *argp){}

//! @todo
static void* _xnr_object_dtor(void *_self){}

//! @todo
static int _xnr_object_differ(const void *_self, const void *b){}

//! @todo
static int _xnr_object_puto(const void *_self, FILE *fp){}

//! @todo
const void *xnr_classof(const void *_self){}

//! @todo
size_t xnr_sizeof(const void *_self){}

// -- xnr_class --
//! @todo
static void* _xnr_class_ctor(void *_self, va_list *argp){}

//! @todo
static void* _xnr_class_dtor(void *_self){}

//! @todo
const void* xnr_super(const void *_self){}

// -- initialization --
static const xnr_class_t object[] = {
    {
        {object+1},
        "Object", object, sizeof(xnr_object_t),
        _xnr_object_ctor, _xnr_object_dtor,
        _xnr_object_differ, _xnr_object_puto
    },
    {
        {object+1},
        "Class", object, sizeof(xnr_class_t),
        _xnr_class_ctor, _xnr_class_dtor,
        _xnr_object_differ, _xnr_object_puto
    }
};

const void *xnr_object = object;
const void *xnr_class = object + 1;

// -- object management and selectors ---

void* xnr_new(const void *_klass, ...){
    const xnr_class_t *klass = _klass;
    xnr_object_t *object;
    va_list ap;

    assert(klass && klass->size);
    object = calloc(1, klass->size);
    assert(object);
    object->klass = klass;
    va_start(ap, _klass);
    object = xnr_ctor(object, &ap);
    va_end(ap);

    return object;
}

//
void xnr_delete(void *self){
    if(self){
        free(xnr_dtor(self));
    }
}

void* xnr_ctor(void *self, va_list *argp){
    const xnr_class_t *klass = xnr_classof(self);

    assert(klass->ctor);
    return klass->ctor(self, argp);
}

void* xnr_super_ctor(const void *_klass, void *self, va_list *argp){
    const xnr_class_t *superclass = xnr_super(_klass);
    assert(self && superclass->ctor);
    return superclass->ctor(self, argp);
}
