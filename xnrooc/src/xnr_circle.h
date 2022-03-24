#ifndef _XNR_CIRCLE_H
#define _XNR_CIRCLE_H

#include "xnr_point.h"

typedef struct xnr_circle_{
    const xnr_point_t _;
    int rad;
}xnr_circle_t;

extern const void *xnr_circle;
void xnr_init_circle(void);

#endif
