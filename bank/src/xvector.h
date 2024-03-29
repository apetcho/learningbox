#ifndef _XVECTOR_H
#define _XVECTOR_H
#include<stddef.h>
#include<assert.h>

typedef struct XVector_t XVector_t;
typedef void* (*ItemAllocator)(size_t);
typedef void (*ItemDeallocator)(void *);
typedef void (*ItemCopyFn)(void *to, const void *from);

// ctor & dtor operations
XVector_t* vector_malloc(size_t capacity, size_t itemsize);
void vector_free(XVector_t *vec);
// access operations
int vector_push_back(XVector_t *vec, const void *var);
void vector_pop_back(XVector_t *vec, void *var);
void* vector_get_item( XVector_t *vec, size_t index);
void* vector_get_begin(XVector_t *vec);
void* vector_get_end(XVector_t *vec);
// size operations
size_t vector_get_itemsize(const XVector_t *vec);
size_t vector_get_size(const XVector_t *vec);
size_t vector_get_capacity(const XVector_t *vec);
int vector_set_size(XVector_t *vec, size_t size);
int vector_set_capacity(XVector_t *vec, size_t capacity);


#if !defined(MAKE_CUSTOM_XVECTOR)
//#undef MAKE_CUSTOM_XVECTOR
//#endif
#define MAKE_CUSTOM_XVECTOR(T)                                          \
    XVector_t* vector_malloc_ ## T (size_t capacity){                   \
        return vector_malloc(capacity, sizeof(T));                      \
    }                                                                   \
    int vector_push_back_ ## T (XVector_t *vec, const T *item){         \
        assert(vector_get_itemsize(vec) == sizeof(T));                  \
        return vector_push_back(vec, (const void*)item);                \
    }                                                                   \
    T* vector_pop_back_ ## T (XVector_t *vec){                          \
        assert(vector_get_itemsize(vec) == sizeof(T));                  \
        T *item;                                                        \
        vector_pop_back(vec, (void*)item);                              \
        return item;                                                    \
    }                                                                   \
    T* vector_get_item_ ## T(XVector_t *vec, size_t index){       \
        assert(vector_get_itemsize(vec) == sizeof(T));                  \
        T *item;                                                        \
        item = (T*)vector_get_item(vec, index);                         \
        return item;                                                    \
    }                                                                   \
    T* vector_get_begin_ ## T(XVector_t *vec){                          \
        assert(vector_get_itemsize(vec) == sizeof(T));                  \
        T *item;                                                        \
        item = (T*)vector_get_begin(vec);                               \
        return item;                                                    \
    }                                                                   \
    T *vector_get_end_ ## T(XVector_t *vec){                            \
        assert(vector_get_itemsize(vec) == sizeof(T));                  \
        T *item;                                                        \
        item = (T*)vector_get_end(vec);                                 \
        return item;                                                    \
    }
#endif

#endif
