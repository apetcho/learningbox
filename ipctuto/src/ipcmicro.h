#ifndef __IPCMICRO_H_
#define __IPCMICRO_H_
#include<pthread.h>
#include<stdio.h>

#undef SIMPLE_SHARED
#define SIMPLE_MUTEX

#ifdef SIMPLE_MUTEX
    #define STRUCT_MUTEX
    #if !defined(USE_MUTEX)
    #   define USE_MUTEX
    #endif
#endif

#ifdef SIMPLE_SHARED
#if defined(USE_MUTEX)
#undef USE_MUTEX
#endif
#endif

#undef USE_MUTEX
#ifdef SIMPLE_SHARED
#define USE_MUTEX
#endif


void ipcmicro_perror(char *message);
void* ipcmicro_malloc(size_t size);

#ifdef USE_MUTEX
#ifdef STRUCT_MUTEX
    struct Mutex;
    typedef struct Mutex Mutex;
#else
    typedef pthread_mutex_t Mutex;
#endif

Mutex* simple_new_mutex();
void simple_lock(Mutex *mutex);
void simple_unlock(Mutex *mutex);
#endif

typedef void* (ThreadCallback_t)(void *);
struct SharedData;
typedef struct SharedData SharedData;

pthread_t simple_new_thread(ThreadCallback_t fn, SharedData *shared);
void simple_join_thread(pthread_t thread);

void simple_child(SharedData *shared);
void* simple_callback(void *arg);

SharedData* simple_new_shared_data(int n);

// -----------------------
#ifdef SIMPLE_MUTEX
typedef struct Mutex{
    pthread_mutex_t mutex[1];
} Mutex;

struct SharedData{
    int counter;
    Mutex *mutex;
};

#endif // SIMPLE_MUTEX 

// ----------------------------
#ifdef SIMPLE_SHARED

struct SharedData{
    int counter;
};
#endif

// 

#endif // __IPCMICRO_H_
