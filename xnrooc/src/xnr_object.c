#include<stdarg.h>
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
void* xnr_new(const void *klass, ...){}

//
void xnr_delete(void *item){}

//
void* xnr_clone(const void *self){}

//
int xnr_differ(const void *self, const void *other){}

//
size_t xnr_sizeof(const void *self){}
