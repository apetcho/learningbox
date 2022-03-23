#ifndef _XNR_POINT_H
#define _XNR_POINT_H

typedef struct /*xnr_point_*/{
    const void *klass;
    int x;
    int y;
} xnr_point_t;

extern const void *xnr_point;

void xnr_point_move(void *point, int dx, int dy);

#define XNR_GETX(p)     (((const xnr_point_t*)(p))->x)
#define XNR_GETY(p)     (((const xnr_point_t*)(p))->y)

#endif
