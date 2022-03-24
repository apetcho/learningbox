#include<stdio.h>
#include<stdarg.h>

#include "xnr_circle.h"


static void *_xnr_circle_ctor(void *_self, va_list *argp){
    xnr_circle_t *self = xnr_super_ctor(xnr_circle, _self, argp);
    self->rad = va_arg(*argp, int);
    return self;
}

static void _xnr_circle_draw(const void *_self){
    const xnr_circle_t *self = _self;
    printf(
        "<circle x=%d y=%d radius=%d>\n",
        XNR_GETX(self), XNR_GETY(self), self->rad
    );
}


//
static const xnr_class_t _Circle = {
    sizeof(xnr_circle_t),
    _xnr_circle_ctor,
    0,
    _xnr_circle_draw
};

const void *xnr_circle = &_Circle;
