#include<stdarg.h>
#include<stdlib.h>
#include<assert.h>
#include<stdio.h>
#include<string.h>

#include "xnr_object.h"

// -- object --

static void* _xnr_object_ctor(void *self, va_list *argp){
    return self;
}


static void* _xnr_object_dtor(void *self){ return self; }

//
static int _xnr_object_differ(const void *self, const void *other){
    return self != other;
}

//
static int _xnr_object_puto(const void *self, FILE *fp){
    const xnr_class_t *klass = xnr_classof(self);
    return fprintf(fp, "%s at %p\n", klass->name, self);
}

//
const void *xnr_classof(const void *_self){
    const xnr_object_t *self = _self;
    assert(self && self->klass);
    return self->klass;
}

//
size_t xnr_sizeof(const void *self){
    const xnr_class_t *klass = xnr_classof(self);
    return klass->size;
}

// -- xnr_class --
//
static void* _xnr_class_ctor(void *_self, va_list *argp){
    xnr_class_t *self = _self;
    const size_t offset = offsetof(xnr_class_t, ctor);

    self->name = va_arg(*argp, char*);
    self->super = va_arg(*argp, xnr_class_t*);
    self->size = va_arg(*argp, size_t);

    assert(self->super);
    memcpy(
        (char*)self+offset,
        (char*)self->super+offset,
        xnr_sizeof(self->super)-offset
    );

    {
        typedef void (*voidf)();
        voidf selector;
#ifdef va_copy
        va_list ap;
        va_copy(ap, *argp);
#else
        va_list ap = *argp;
#endif
        while((selector = va_arg(ap, voidf))){
            voidf method = va_arg(ap, voidf);
            if(selector == (voidf)xnr_ctor){
                *(voidf *)&self->ctor = method;
            }else if(selector == (voidf)xnr_dtor){
                *(voidf*)&self->dtor = method;
            }else if(selector == (voidf)xnr_differ){
                *(voidf*)&self->differ = method;
            }else if(selector == (voidf)xnr_puto){
                *(voidf*)&self->puto = method;
            }
        }
#ifdef va_copy
        va_end(ap);
#endif
        return self;
    }
}

//
static void* _xnr_class_dtor(void *_self){
    xnr_class_t *self = _self;
    fprintf(stderr, "%s: cannot destroy class\n", self->name);
    return 0;
}

//
const void* xnr_super(const void *_self){
    const xnr_class_t *self = _self;
    assert(self && self->super);
    return self->super;
}

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

void* xnr_dtor(void *self){
    const xnr_class_t *klass = xnr_classof(self);
    assert(klass->dtor);
    return klass->dtor(self);
}

void* xnr_super_dtor(const void *klass, void *self){
    const xnr_class_t *superclass = xnr_super(klass);
    assert(self && superclass->dtor);
    return superclass->dtor(self);
}

int xnr_differ(const void *self, const void *other){
    const xnr_class_t *klass = xnr_classof(self);
    assert(klass->differ);
    return klass->differ(self, other);
}

int xnr_super_differ(const void *klass, const void *self, const void *other){
    const xnr_class_t *superclass = xnr_super(klass);
    assert(superclass->differ);
    return superclass->differ(self, other);
}

int xnr_puto(const void *self, FILE *fp){
    const xnr_class_t *klass = xnr_classof(self);
    assert(klass->puto);
    return klass->puto(self, fp);
}

int xnr_super_puto(const void *klass, const void *self, FILE *fp){
    const xnr_class_t *superclass = xnr_super(klass);
    assert(superclass->puto);
    return superclass->puto(self, fp);
}
