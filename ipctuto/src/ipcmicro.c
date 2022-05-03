
#include<stdlib.h>
#include"ipcmicro.h"

#define NUM_CHILDREN 5


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

#ifdef SIMPLE_MUTEX

Mutex* simple_new_mutex(){
    size_t size = sizeof(Mutex);
    Mutex *mutex = (Mutex*)ipcmicro_malloc(size);
    pthread_mutex_init(mutex->mutex, NULL);
    return mutex;
}

void simple_lock(Mutex *mutex){
    pthread_mutex_lock(mutex->mutex);
}

void simple_unlock(Mutex *mutex){
    pthread_mutex_unlock(mutex->mutex);
}

SharedData* simple_new_shared_data(int n){
    SharedData *shared = ipcmicro_malloc(sizeof(SharedData));
    shared->counter = 0;
    shared->mutex = simple_new_mutex();
    return shared;
}

pthread_t simple_new_thread(ThreadCallback_t fn, SharedData *shared){}
void simple_join_thread(pthread_t thread){}

void simple_child(SharedData *shared){}
void* simple_callback(SharedData *arg){}


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
