#include<stdlib.h>
#include<stdio.h>
#include<assert.h>
#include<string.h>
#include<time.h>

#include "xvector.h"

typedef struct{
    char *name;
    int age;
}Person_t;

void copyInt(void *a, const void *b){
    int *value = (int*)malloc(sizeof(int));
    assert(value);
    *value = *(int*)b;
    a = (void*)value;
}

void testStruct(){
    Person_t people[] = {
        [0] = {"Eyram", 22},
        [1] = {"John", 30},
        [2] = {"Sven", 27},
        [3] = {"Oli", 44},
        [4] = {"Chris", 32},
        [5] = {"Alain", 23},
        [6] = {"Vladmir", 30},
        [7] = {"Emmanuel", 33},
        [8] = {},
        [9] = {},
        [10] = {},
        [11] = {},
        [12] = {},
    };

    size_t N = 8;
    XVector_t *svec = vector_malloc(2, sizeof(Person_t));
    printf("itemsize = %d\n", (int)vector_get_itemsize(svec));
    printf("size = %d\n", (int)vector_get_size(svec));
    printf("capacity = %d\n", (int)vector_get_capacity(svec));
    for(size_t i=0; i < N; i++){
        vector_push_back(svec, &people[i]);
    }
    printf("size = %d\n", (int)vector_get_size(svec));
    printf("capacity = %d\n", (int)vector_get_capacity(svec));
    Person_t p;
    srand((unsigned)time(0));
    for(size_t i=0; i < N / 2; i++){
        size_t idx = (size_t)rand() % N;
        //vector_pop_back(svec, &p);
        printf("idx = %d, ", (int)idx);
        Person_t *x = (Person_t*)vector_get_item(svec, idx);
        printf("name = %s, age = %d\n", x->name, x->age);
    }
    vector_free(svec);
}

// ----
typedef Person_t User;
CUSTOM_XVECTOR(User)

void testUser(){
    Person_t people[] = {
        [0] = {"Eyram", 22}, [1] = {"John", 30}, [2] = {"Sven", 27},
        [3] = {"Oli", 44}, [4] = {"Chris", 32}, [5] = {"Alain", 23},
        [6] = {"Vladmir", 30}, [7] = {"Emmanuel", 33},
    };
    size_t N = 8;

    XVector_t *users = vector_malloc_User(2);
    printf("itemsize = %d\n", (int)vector_get_itemsize(users));
    printf("size = %d\n", (int)vector_get_size(users));
    printf("capacity = %d\n", (int)vector_get_capacity(users));
    for(size_t i=0; i < N; i++){
        vector_push_back_User(users, &people[i]);
        User *user = (User*)vector_pop_back_User(users);
        printf("name = %s, age = %d\n", user->name, user->age);
    }
    printf("size = %d\n", (int)vector_get_size(users));
    printf("capacity = %d\n", (int)vector_get_capacity(users));
    vector_free(users);

    time_t t = time(0);
    printf("%s\n", asctime(localtime(&t)));
}
// ----

int getRandom(){
    return rand() % 100;
}

void testIntVec(){
    srand((unsigned)time(0));
    const size_t CAPACITY = 4;
    int val = 0;
    int index;
    XVector_t *ivec = vector_malloc(CAPACITY, sizeof(int));
    for(size_t i = 0; i < CAPACITY * 2; i++){
        val = getRandom();
        index = vector_push_back(ivec, &val);
        printf("vector_push_back(): ivec[%d] = %d\n", index, val);
    }
    printf("size = %d\n", (int)vector_get_size(ivec));
    printf("capacity = %d\n", (int)vector_get_capacity(ivec));
    printf("itemsize = %d\n", (int)vector_get_itemsize(ivec));
    for(size_t i=0; i < vector_get_size(ivec)/2; i++){
        vector_pop_back(ivec, (void *)&val);
        printf("val = %d\n", val);
    }
    vector_pop_back(ivec, &val);
    printf("val = %d\n", val);
    printf("size = %d\n", (int)vector_get_size(ivec));
    for(size_t i=0; i < vector_get_size(ivec); i++){
        printf("ivec[%d] = %d\n", (int)i, *((int*)vector_get_item(ivec, i)));
    }
    vector_free(ivec);
    

    return;
}

// ----------------------------
//    M A I N   D R I V E R 
// ----------------------------
int main(int argc, char **argv){
    //testIntVec();
    //testStruct();
    testUser();

    return EXIT_SUCCESS;
}
