#ifndef __IPCMICRO_H_
#define __IPCMICRO_H_
#include<pthread.h>
#include<stdio.h>

typedef pthread_mutex_t Mutex;
typedef pthread_cond_t Cond;
typedef void* (ThreadCallback_t)(void *);

typedef struct QueueData{
    int *array;
    int len;
    int nextIn;
    int nextOut;
    Mutex *mutex;
    Cond *nonempty;
    Cond *nonfull;
} QueueData;

typedef struct SharedData {
    QueueData *queue;
} SharedData;

QueueData* simple_new_queue(int len);
int simple_queue_incr(QueueData *queue, int i);
int simple_queue_empty(QueueData *queue);
int simple_queue_full(QueueData *queue);
void simple_queue_push(QueueData *queue, int item);
int simple_queue_pop(QueueData *queue);
void* simple_producer(void *arg);
void* simple_consumer(void *arg);
void simple_queue_test();

// 
Cond* simple_new_cond();
void simple_cond_wait(Cond *cond, Mutex *mutex);
void simple_cond_signal(Cond *cond);

//
Mutex* simple_new_mutex();
void simple_mutex_lock(Mutex *mutex);
void simple_mutex_unlock(Mutex *mutex);

SharedData* simple_new_shared_data();
pthread_t simple_new_thread(ThreadCallback_t fn, SharedData *shared);
void simple_join_thread(pthread_t thread);
void simple_child(SharedData *shared);
void* simple_callback(void *arg);
void ipcmicro_perror(char *message);
void* ipcmicro_malloc(size_t size);

#endif // __IPCMICRO_H_
