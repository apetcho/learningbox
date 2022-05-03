#ifndef __IPCMICRO_H_
#define __IPCMICRO_H_
#include<pthread.h>
#include<stdio.h>


void ipcmicro_perror(char *message);
void* ipcmicro_malloc(size_t size);
typedef void* (ThreadCallback_t)(void *);

#define SIMPLE_SHARED
#undef SIMPLE_COUNTER


#ifdef SIMPLE_COUNTER
typedef struct SimpleCounter{
    pthread_mutex_t mutex[1];
} SimpleCounter;

SimpleCounter simpleCounter_new_mutex();
void simpleCounter_lock(SimpleCounter *mutex);
void simpleCounter_unlock(SimpleCounter *mutex);
#endif 

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
