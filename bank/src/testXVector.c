#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<time.h>

#include "xvector.h"

void copyInt(void *a, void *b){
    *a = *(int*)b;
}

void testIntVec(){
    const size_t CAPACITY = 10;
    int val = 0;
    int index;
    XVector_t *ivec = vector_malloc(
        malloc, free, copyInt, CAPACITY, sizeof(int)
    );
    for(size_t i = 0; i < CAPACITY/2; i++){
        val = rand() % 100;
        index = vector_push_back(ivec, &val);
        printf("vector_push_back(): ivec[%d] = %d\n", index, val);
    }

    vector_free(ivec);

    return;
}

// ----------------------------
//    M A I N   D R I V E R 
// ----------------------------
int main(int argc, char **argv){
    testIntVec();
    return EXIT_SUCCESS;
}
