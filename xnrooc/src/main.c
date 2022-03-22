#include<stdio.h>
#include "xnr_object.h"
#include "xnr_set.h"


int main(){
    void *s = xnr_new(xnr_set);
    void *a = xnr_set_add(s, xnr_new(xnr_object));
    void *b = xnr_set_add(s, xnr_new(xnr_object));
    void *c = xnr_new(xnr_object);

    if(xnr_set_contains(s, a) && xnr_set_contains(s, b)){ puts("OK"); }
    if(xnr_set_contains(s, c)){ puts("contains?"); }
    if(xnr_differ(a, xnr_set_add(s, a))){ puts("differ?"); }
    if(xnr_set_contains(s, xnr_set_drop(s, a))){ puts("drop?"); }

    xnr_delete(xnr_set_drop(s, b));
    xnr_delete(xnr_set_drop(s, c));
    
    return 0;
}
