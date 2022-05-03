
#include<stdlib.h>
#include<string.h>
#include"ipcmicro.h"

#define NUM_CHILDREN 2
#define QUEUE_LENGTH 16
#define NUM_ITEMS   127

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

// ------ QUEUE DATA STRUCTURE --------
QueueData* simple_new_queue(int len){
    QueueData* queue = (QueueData*)ipcmicro_malloc(sizeof(QueueData));
    queue->len = len;
    queue->array = (int*)ipcmicro_malloc((sizeof(QueueData)*len));
    queue->nextIn = 0;
    queue->nextOut = 0;
    // queue->mutex = simple_new_mutex();
    // queue->nonempty = simple_new_cond();
    // queue->nonfull = simple_new_cond();
    queue->mutex = simple_new_semaphore(1);
    queue->items = simple_new_semaphore(0);
    queue->spaces = simple_new_semaphore(len-1);
    return queue;
}

int simple_queue_incr(QueueData *queue, int i){
    return (i+1)% queue->len;
}

int simple_queue_empty(QueueData *queue){
    return (queue->nextIn == queue->nextOut);
}

int simple_queue_full(QueueData *queue){
    return (simple_queue_incr(queue, queue->nextIn) == queue->nextOut);
}

void simple_queue_push(QueueData *queue, int item){
    simple_semaphore_wait(queue->spaces);
    simple_semaphore_wait(queue->mutex);
    queue->array[queue->nextIn] = item;
    queue->nextIn = simple_queue_incr(queue, queue->nextIn);
    simple_semaphore_signal(queue->mutex);
    simple_semaphore_signal(queue->items);
}

int simple_queue_pop(QueueData *queue){
    simple_mutex_lock(queue->mutex);
    while(simple_queue_empty(queue)){
        simple_cond_wait(queue->nonempty, queue->mutex);
    }
    int item = queue->array[queue->nextOut];
    queue->nextOut = simple_queue_incr(queue, queue->nextOut);
    simple_mutex_unlock(queue->mutex);
    simple_cond_signal(queue->nonfull);
    return item;
}


void simple_queue_test(){
    char msg[] = "TESTING SIMPLE QUEUE DATA STRUCTURE";
    size_t size = strlen(msg)+1+2;
    char line[size];
    memset(line, '-', sizeof(line));
    printf("%s\n", line);
    printf(" %s \n", msg);
    printf("%s\n", line);
    int item;
    int len = 128;
    QueueData *queue = simple_new_queue(len);
    if(!simple_queue_empty(queue)){
        ipcmicro_perror("Newly created queue is not empty");
    }
    for(int i=0; i < len; i++){
        simple_queue_push(queue, i);
    }
    if(!simple_queue_full(queue)){
        ipcmicro_perror("Fully loaded queue should be full");
    }
    for(int i=0; i < 10; i++){
        item = simple_queue_pop(queue);
        if(!(item==i)){
            ipcmicro_perror("Weird order of item in queue");
        }
    }
    if(simple_queue_empty(queue)){
        ipcmicro_perror("Queue should not be empty at this moment");
    }
    if(simple_queue_full(queue)){
        ipcmicro_perror("Queue should not be full at this moment");
    }
}


// ------- END OF QUEUE DS -------


// --------- SHARE DATA ALLOCATION --------------
SharedData* simple_new_shared_data(){
    SharedData *shared = ipcmicro_malloc(sizeof(SharedData));
    shared->queue = simple_new_queue(128);
    return shared;
}

// --------- END OF SHARE DATA ALLOCATION --------

// --------- THREAD UTILS ---------
pthread_t simple_new_thread(ThreadCallback_t callback, SharedData *shared){
    int retval;
    pthread_t thread;
    retval = pthread_create(&thread, NULL, callback, (void*)shared);
    if(retval != 0){
        ipcmicro_perror("pthread_create failed");
    }
    return thread;
}

void simple_join_thread(pthread_t thread){
    int retval = pthread_join(thread, NULL);
    if(retval == -1){
        ipcmicro_perror("pthread_join failed");
    }
}

// ----------- END OF THREAD UTILS --------

// ----------- Conditional Variable Utils -------------
Cond* simple_new_cond(){
    Cond *cond = ipcmicro_malloc(sizeof(Cond));
    if((pthread_cond_init(cond, NULL) != 0)){
        ipcmicro_perror("pthread_cond_init() failed");
    }
    return cond;
}

void simple_cond_wait(Cond *cond, Mutex *mutex){
    if((pthread_cond_wait(cond, mutex))!=0){
        ipcmicro_perror("pthread_cond_wait() failed");
    }
}

void simple_cond_signal(Cond *cond){
    if((pthread_cond_signal(cond)) != 0){
        ipcmicro_perror("pthread_cond_signal() failed");
    }
}

// ----------- End Of Conditional Variable Utils ------

// ----------- SEMAPHORE UTILS ------------
Semaphore* simple_new_semaphore(int value){
    Semaphore *sem = ipcmicro_malloc(sizeof(Semaphore));
    if((sem_init(sem, 0, value)) != 0){
        ipcmicro_perror("sem_init() failed");
    }

    return sem;
}

void simple_semaphore_wait(Semaphore *sem){
    if((sem_wait(sem)) != 0){
        ipcmicro_perror("sem_wait() failed");
    }
}

void simple_semaphore_signal(Semaphore *sem){
    if((sem_post(sem)) != 0){
        ipcmicro_perror("sem_post() failed");
    }
}

// ------ END OF SEMAPHORE UTILS ----------

// ----------- PRODUCER / CONSUMER --------
void* simple_producer(void *arg){
    SharedData *shared = (SharedData*)arg;
    for(int i=0; i < QUEUE_LENGTH; i++){
        printf("\x1b[32mProducing\x1b[m item \x1b[34m%d\x1b[m to queue\n", i);
        simple_queue_push(shared->queue, i);
    }
    pthread_exit(NULL);
}

void* simple_consumer(void *arg){
    int item;
    SharedData *shared = (SharedData*)arg;
    for(int i=0; i < QUEUE_LENGTH; i++){
        item = simple_queue_pop(shared->queue);
        printf(
            "\x1b[35mConsuming\x1b[m item \x1b[33m%d\x1b[m from queue\n", item
        );
    }

    pthread_exit(NULL);
}

// --------- MUTEX UTILS ---------
Mutex* simple_new_mutex(){
    Mutex *mutex = ipcmicro_malloc(sizeof(Mutex));
    int n = pthread_mutex_init(mutex, NULL);
    if(n != 0){
        ipcmicro_perror("pthread_mutex_init() faild");
    }
    return mutex;
}

void simple_mutex_lock(Mutex *mutex){
    int n = pthread_mutex_lock(mutex);
    if(n != 0){
        ipcmicro_perror("pthread_mutex_lock() failed");
    }
}

void simple_mutex_unlock(Mutex *mutex){
    int n = pthread_mutex_unlock(mutex);
    if(n != 0){
        ipcmicro_perror("pthread_mutex_unlock() failed");
    }
}

// ------ END OF MUTEX UTILS -----

// -----------------------------
// -------- MAIN DRIVER --------
// -----------------------------
int main(int argc, char **argv){
#undef TEST_QUEUE
#ifdef TEST_QUEUE
    simple_queue_test();
#else
    pthread_t child[NUM_CHILDREN];
    SharedData *data = simple_new_shared_data();
    child[0] = simple_new_thread(simple_producer, data);
    child[1] = simple_new_thread(simple_consumer, data);

    for(int i=0; i < NUM_CHILDREN; i++){
        simple_join_thread(child[i]);
    }
#endif
    // if(data->queue->array){
    //     free(data->queue->array);
    //     data->queue->array = NULL;
    // }
    // if(data->queue){
    //     data->queue->mutex = NULL;
    //     free(data->queue);
    // }
    // if(data){
    //     free(data);
    //     data = NULL;
    // }

    return 0;
}
