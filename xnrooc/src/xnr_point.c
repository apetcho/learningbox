#include<assert.h>

#include "xnr_point.h"

//!@todo
static void* _xnr_point_ctor(void *_self, va_list *argp){
    xnr_point_t *self = xnr_super_ctor(xnr_point, _self, argp);
    self->x = va_arg(*argp, int);
    self->y = va_arg(*argp, int);
    return self;
}

//!@todo
static void _xnr_point_draw(const void *_self){
    const xnr_point_t *self = _self;
    printf("<point x=%d, y=%d>\n", self->x, self->y);
}

//!@todo
void xnr_draw(const void *_self){}

//!@todo
void xnr_super_draw(const void *klass, const void *self){}

//!@todo
void xnr_move(void *_self, int dx, int dy){}

//!@todo
static void* _xnr_point_class_ctor(void *_self, va_list *argp){}

// -- initialization --
const void *xnr_point_class;
const void *xnt_point;

//!@todo
void xnr_init_point(void){}
