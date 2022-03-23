#ifndef _XNR_POINT_H
#define _XNR_POINT_H

#include "xnr_object.h"

typedef struct xnr_point_ xnr_point_t;
typedef struct xnr_point_class_ xnr_point_class_t;

struct xnr_point_{
    const xnr_object_t _;   /* xnr_point: xnr_object */
    int x;
    int y;
};

struct xnr_point_class_{
    const xnr_class_t _;    /* xnr_point_class : xnr_class */
    void (*draw)(const void *self);
};

extern const void *xnr_point;
extern const void *xnr_point_class;

void xnr_super_draw(const void *klass, const void *self);
void xnr_draw(const void *self);
void xnr_move(void *point, int dx, int dy);
void xnr_init_point(void);


#define XNR_GETX(p)     (((const xnr_point_t*)(p))->x)
#define XNR_GETY(p)     (((const xnr_point_t*)(p))->y)

#endif
