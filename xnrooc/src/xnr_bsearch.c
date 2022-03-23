#include<string.h>
#include "xnr_bsearch.h"

void* xnr_bsearch(
    const void* key, void *_base, size_t *nelp, size_t width,
    int (*cmp)(const void *key, const void *elt)
)
{
    size_t nel = *nelp;

#define _XNR_BASE (*(char**)&_base)

    char *lim = _XNR_BASE + nel * width;
    char *high;

    if(nel > 0){
        for(high = lim - width; _XNR_BASE <= high; nel >>=1){
            char *mid = _XNR_BASE + (nel >> 1)*width;
            int c = cmp(key, mid);
            if(c < 0){ high = mid - width; }
            else if(c > 0){
                _XNR_BASE = mid + width;
                --nel;
            }else{
                return (void*)mid;
            }
        }
        memmove(_XNR_BASE + width, _XNR_BASE, lim - _XNR_BASE);
    }
    ++ *nelp;
    return memcpy(_XNR_BASE, key, width);
#undef _XNR_BASE
}
