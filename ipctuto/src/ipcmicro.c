
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
#define NUM_CHILDREN 5

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

void simpleShared_join_thread(pthread_t thread){
    int retval = pthread_join(thread, NULL);
    if(retval == -1){
        ipcmicro_perror("pthread_join failed");
    }
}

void* sscallback(void *arg){
    SimpleShared *shared = (SimpleShared*)arg;
    simpleShared_child(shared);
    pthread_exit(NULL);
}

#endif


// -----------------------------
// -------- MAIN DRIVER --------
// -----------------------------
int main(int argc, char **argv){
#ifdef SIMPLE_SHARED
    pthread_t children[NUM_CHILDREN];
    SimpleShared *shared = simpleShared_new(100000);
    for(int i=0; i < NUM_CHILDREN; i++){
        children[i] = simpleShared_new_thread(sscallback, shared);
    }

    for(int i=0; i < NUM_CHILDREN; i++){
        simpleShared_join_thread(children[i]);
    }

#endif

    return 0;
}
