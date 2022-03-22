#include<stdlib.h>
#include<string.h>
#include<stdarg.h>
#include<assert.h>

#include "xnr_object.h"
#include "xnr_string.h"

//
typedef struct xnr_string_ xnr_string_t;
struct xnr_string_{
    const void *klass;
    char *text;
    xnr_string_t *next;
    unsigned count;
};

//
static xnr_string_t *ring;

// --
static void* _string_ctor(void *_self, va_list *args){
    xnr_string_t *self = _self;
    const char *text = va_arg(*args, const char *);
    if(ring){
        xnr_string_t *ptr = ring;
        do{
            if(strcmp(ptr->text, text) == 0){
                ++ptr->count;
                free(self);
                return ptr;
            }
        }while((ptr = ptr->next) != ring);
    }else{
        ring = self;
    }

    self->next = ring->next;
    ring->next = self;
    self->count = 1;
    self->text = malloc(strlen(text)+1);
    assert(self->text);
    strcpy(self->text, text);

    return self;
}

static void* _string_dtor(void *_self){}
static void* _string_clone(const void *_self){}
static int _string_differ(const void *self, const void *other){}


//
static const xnr_class _String = {
    sizeof(xnr_string_t),
    _string_ctor,
    _string_dtor,
    _string_clone,
    _string_differ
};

const void *xnr_string = &_String;
