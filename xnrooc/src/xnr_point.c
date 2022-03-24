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

//
void xnr_move(void *_self, int dx, int dy){
    xnr_point_t *self = _self;
    self->x += dx;
    self->y += dy;
}

//
static void* _xnr_point_class_ctor(void *_self, va_list *argp){
    xnr_point_class_t *self = xnr_super_ctor(xnr_point_class, _self, argp);
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
        if(selector == (voidf)xnr_draw){
            *(voidf*)&self->draw = method;
        }
    }
#ifdef va_copy
    va_end(ap);
#endif
    return self;
}

// -- initialization --
const void *xnr_point_class;
const void *xnr_point;
//
void xnr_init_point(void){
    if(!xnr_point_class){
        xnr_point_class = xnr_new(
            xnr_class, "PointClass",
            xnr_class, sizeof(xnr_point_class_t),
            xnr_ctor, _xnr_point_class_ctor, 0
        );
    }
    if(!xnr_point){
        xnr_point = xnr_new(
            xnr_point_class, "Point",
            xnr_object, sizeof(xnr_point_t),
            xnr_ctor, _xnr_point_class_ctor,
            xnr_draw, _xnr_point_draw, 0
        );
    }
}
