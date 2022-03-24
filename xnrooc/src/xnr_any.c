#include "xnr_object.h"

static int _xnr_any_differ(const void *self, const void* other){ return 0; }

int main(){
    void *obj = xnr_new(xnr_object);
    const void *any = xnr_new(
        xnr_class, "Any", xnr_object,
        xnr_sizeof(obj), xnr_differ,
        _xnr_any_differ, 0
    );

    void *a = xnr_new(any);
    xnr_puto(any, stdout);
    xnr_puto(obj, stdout);
    xnr_puto(a, stdout);

    if(xnr_differ(obj, obj) == xnr_differ(a, a)){ puts("OK"); }

    if(xnr_differ(obj, a) != xnr_differ(a, obj)){
        puts("not commutative");
    }

    xnr_delete(obj);
    xnr_delete(a);
    xnr_delete((void*)any);

    return 0;
}
