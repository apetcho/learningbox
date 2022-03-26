#include<stdlib.h>
#include<string.h>
#include<assert.h>
#include<errno.h>
#include<stdio.h>

#include "xvector.h"

static const int DEFAULT_CAPACITY = 2;
static const double GROWTH_RATE = 1.5;

struct XVector_{
    void *data;
    size_t capacity;
    size_t size;
    size_t itemsize;
    ItemAllocator allocate;
    ItemDeallocator deallocate;
};

