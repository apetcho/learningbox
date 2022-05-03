
#include<stdlib.h>
#include"ipcmicro.h"

//
void ipcmicro_perror(char *message){
    perror(message);
    exit(-1);
}

void* ipcmicro_malloc(size_t size){
    void *data = malloc(size);
    if(data == NULL){
        ipcmicro_perror("malloc failed");
    }
    return data;
}

#ifdef SIMPLE_SHARED

SimpleShared* simpleShared_new(int n){
    SimpleShared *shared = ipcmicro_malloc(sizeof(SimpleShared));
    shared->counter = 0;
    (void)n;
    return shared;
}

pthread_t simpleShared_new_thread(ThreadCallback_t fn, SimpleShared *shared){
    int retval;
    pthread_t thread;
    retval = pthread_create(&thread, NULL, fn, (void*)shared);
    if(retval != 0){
        ipcmicro_perror("pthread_create failed");
    }

    return thread;
}

#endif
