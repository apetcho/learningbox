#include<assert.h>

#include "xnr_point.h"

//
static void* _xnr_point_ctor(void *_self, va_list *argp){
    xnr_point_t *self = xnr_super_ctor(xnr_point, _self, argp);
    self->x = va_arg(*argp, int);
    self->y = va_arg(*argp, int);
    return self;
}

//
static void _xnr_point_draw(const void *_self){
    const xnr_point_t *self = _self;
    printf("<point x=%d, y=%d>\n", self->x, self->y);
}

//
void xnr_draw(const void *_self){
    const xnr_point_class_t *klass = xnr_classof(_self);
    assert(klass->draw);
    klass->draw(_self);
}

//
void xnr_super_draw(const void *klass, const void *self){
    const xnr_point_class_t *superclass = xnr_super(klass);
    assert(self && superclass->draw);
    superclass->draw(self);
}

//!@todo
void xnr_move(void *_self, int dx, int dy){}

//!@todo
static void* _xnr_point_class_ctor(void *_self, va_list *argp){}

// -- initialization --
const void *xnr_point_class;
const void *xnt_point;

//!@todo
void xnr_init_point(void){}
