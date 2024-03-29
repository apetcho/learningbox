#include<stdlib.h>
#include<string.h>
#include<stdarg.h>
#include<assert.h>

#include "xnr_object.h"
#include "xnr_string.h"

typedef struct xnr_string_s{
    const void *klass; // super class: must be first
    char *text;
}xnr_string_t;

//
static void* _string_ctor(void *_self, va_list *args){
    xnr_string_t *self = _self;
    const char *text = va_arg(*args, const char*);
    self->text = malloc(strlen(text)+1);
    assert(self->text);
    strcpy(self->text, text);
    return self;
}

//
static void* _string_dtor(void *_self){
    xnr_string_t *self = _self;
    free(self->text);
    self->text = 0;

    return self;
}

//
static void* _string_clone(const void *_self){
    const xnr_string_t *self = _self;
    return xnr_new(xnr_string, self->text);
}

//
static int _string_differ(const void *_self, const void *_other){
    const xnr_string_t *self = _self;
    const xnr_string_t *other = _other;
    if(self==other){ return 0; }
    if( !other || other->klass != xnr_string){ return 1;}
    return strcmp(self->text, other->text);
}

static const xnr_class _String = {
    sizeof(xnr_string_t),
    _string_ctor,
    _string_dtor,
    _string_clone,
    _string_differ
};

const void *xnr_string = &_String;
