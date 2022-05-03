#ifndef __IPCMICRO_H_
#define __IPCMICRO_H_
#include<pthread.h>
#include<stdio.h>


void ipcmicro_perror(char *message);
void* ipcmicro_malloc(size_t size);
typedef void* (ThreadCallback_t)(void *);
struct SharedData;
typedef struct SharedData SharedData;
#define STRUCT_MUTEX
#ifdef STRUCT_MUTEX
    struct Mutex;
    typedef struct Mutex Mutex;
#else
    typedef pthread_mutex_t Mutex;
#endif

Mutex* simple_new_mutex();
void simple_lock(Mutex *mutex);
void simple_unlock(Mutex *mutex);

pthread_t simple_new_thread(ThreadCallback_t fn, SharedData *shared);
void simple_join_thread(pthread_t thread);

void simple_child(SharedData *shared);
void* simple_callback(SharedData *arg);

SharedData* simple_new_shared_data(int n);



#undef SIMPLE_SHARED
#define SIMPLE_MUTEX


#ifdef SIMPLE_MUTEX
typedef struct Mutex{
    pthread_mutex_t mutex[1];
} Mutex;

struct SharedData{
    int counter;
    Mutex *mutex;
};


#endif // SIMPLE_MUTEX 

#ifdef SIMPLE_SHARED

typedef struct SimpleShared{
    int counter;
} SimpleShared;
SimpleShared* simpleShared_new(int n);
pthread_t simpleShared_new_thread(ThreadCallback_t fn, SimpleShared *shared);
void simpleShared_join_thread(pthread_t thread);

static inline void simpleShared_child(SimpleShared *shared){
    printf("counter = %d\n", shared->counter);
    shared->counter++;
}

#endif

// 

#endif
