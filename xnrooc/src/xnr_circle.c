#include<stdio.h>
#include<stdarg.h>

#include "xnr_circle.h"
#include "xnr_object.h"

static void *_xnr_circle_ctor(void *_self, va_list *args){}

static void _xnr_circle_draw(const void *_self){}


//
static const xnr_class _Circle = {
    sizeof(xnr_circle_t),
    _xnr_circle_ctor,
    0,
    _xnr_circle_draw
};

const void *xnr_circle = &_Circle;
