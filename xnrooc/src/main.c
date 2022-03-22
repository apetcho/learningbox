#include<stdio.h>
#include "xnr_object.h"
#include "xnr_string.h"


int main(){
    void *a = xnr_new(xnr_string, "a");
    void **aa = xnr_clone(a);
    void *b = xnr_new(xnr_string, "b");

    printf("xnr_len(a) == %lu\n", (unsigned long)xnr_len(a));
    if(xnr_differ(a, b)){ puts("OK"); }
    if(xnr_differ(a, aa)){ puts("differ?");}

    if(a == aa){ puts("clone?"); }
    xnr_delete(a);
    xnr_delete(aa);
    xnr_delete(b);

    return 0;
}
