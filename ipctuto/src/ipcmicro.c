
#include<stdlib.h>
#include<string.h>
#include"ipcmicro.h"

#define NUM_CHILDREN 2
#define QUEUE_LENGTH 16

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
    QueueData* queue = ipcmicro_malloc(sizeof(QueueData));
    queue->len = len;
    queue->array = (int*)ipcmicro_malloc((sizeof(QueueData)*len));
    queue->nextIn = 0;
    queue->nextOut = 0;

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
    if(simple_queue_full(queue)){
        ipcmicro_perror("Queue is full");
    }
    queue->array[queue->nextIn] = item;
    queue->nextIn = simple_queue_incr(queue, queue->nextIn);
}

int simple_queue_pop(QueueData *queue){
    if(simple_queue_empty(queue)){
        ipcmicro_perror("Queue is empty");
    }
    int item = queue->array[queue->nextOut];
    queue->nextOut = simple_queue_incr(queue, queue->nextOut);
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


SharedData* simple_new_shared_data(){
    SharedData *shared = ipcmicro_malloc(sizeof(SharedData));
    shared->queue = simple_new_queue(QUEUE_LENGTH);
    return shared;
}

pthread_t simple_new_thread(ThreadCallback_t fn, SharedData *shared){
    int retval;
    pthread_t thread;
    retval = pthread_create(&thread, NULL, fn, (void*)shared);
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
            "\x1b[35mProducing\x1b[m item \x1b[34m%d\x1b[m from queue\n", item
        );
    }

    pthread_exit(NULL);
}

#undef TEST_QUEUE
// -----------------------------
// -------- MAIN DRIVER --------
// -----------------------------
int main(int argc, char **argv){
#define TEST_QUEUE
#ifdef TEST_QUEUE
    simple_queue_test();
#else
    pthread_t child[NUM_CHILDREN];
    SharedData *shared = simple_new_shared_data();
    child[0] = simple_new_thread(simple_producer, shared);
    child[1] = simple_new_thread(simple_consumer, shared);

    for(int i=0; i < NUM_CHILDREN; i++){
        simple_join_thread(child[i]);
    }
#endif

    return 0;
}
