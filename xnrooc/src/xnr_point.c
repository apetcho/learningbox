#include<stdio.h>
#include<stdarg.h>

#include "xnr_point.h"
#include "xnr_object.h"

static void* _xnr_point_ctor(void *_self, va_list *args){
    xnr_point_t *self = _self;
    self->x = va_arg(*args, int);
    self->y = va_arg(*args, int);
    return self;
}

static void _xnr_point_draw(const void *_self){
    const xnr_point_t *self = _self;
    printf("\".\" @(%d, %d)\n", self->x, self->y);
}

static const xnr_class _Point = {
    sizeof(xnr_point_t),
    _xnr_point_ctor,
    0,
    _xnr_point_draw
};

const void *xnr_point = &_Point;

void xnr_point_move(void *_self, int dx, int dy){
    xnr_point_t *self = _self;
    self->x += dx;
    self->y += dy;
}
