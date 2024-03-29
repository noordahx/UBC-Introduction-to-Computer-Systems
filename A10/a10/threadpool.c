#include <stdlib.h>
#include "uthread.h"
#include "uthread_mutex_cond.h"
#include "threadpool.h"
#include <stdio.h>

typedef struct Node Node;
typedef struct Queue Queue;



struct Node {
    void(*f)(tpool_t, void*);
    void* args;
    Node *next;
};

struct Queue {
    Node *start;
    Node *end;
};


struct tpool {
    // TODO
    unsigned int max_threads;
    unsigned int running;

    Queue q;
    int flag;
    uthread_mutex_t mutex;
    uthread_cond_t available;
    uthread_cond_t done;
    uthread_t *threads;
};

/**
 * Base procedure of every worker thread.  Calls available tasks
 * or blocks until a task becomes available.
 */
void *worker_thread(void *pool_v) {
    tpool_t pool = pool_v;
    while (1) {

        uthread_mutex_lock(pool->mutex);
        // printf("Mutex: locking\n");
        while (pool->q.start == NULL && pool->flag == 0) 
            uthread_cond_wait(pool->available);
        // printf("Mutex: executing\n");

        if(pool->q.start == NULL && pool->flag){
            uthread_mutex_unlock(pool->mutex);
            break;
        }

        void(*f)(tpool_t, void*) = pool->q.start->f;
        void(*args) = pool->q.start->args;

        Node * temp = pool->q.start;
        pool->q.start = pool->q.start->next;
        free(temp);
        
        pool->running++;

        uthread_mutex_unlock(pool->mutex);

        f(pool, args);

        uthread_mutex_lock(pool->mutex);

        pool->running--;
    
        if (pool->running == 0 && pool->q.start == NULL)
            uthread_cond_signal(pool->done);

        uthread_mutex_unlock(pool->mutex);

    }
    // TODO
    // return NULL; // TODO: replace this placehold return value
}

/**
 * Create a new thread pool with max_threads thread-count limit.
 */
tpool_t tpool_create(unsigned int max_threads) {
    // TODO
    tpool_t pool = malloc(sizeof(*pool));

    pool->max_threads = max_threads;
    pool->running = 0;
    pool->q.start = NULL;
    pool->q.end = NULL;
    
    pool->threads = malloc(max_threads * sizeof(*(pool->threads)));
    pool->flag = 0;
    pool->mutex = uthread_mutex_create();
    pool->available = uthread_cond_create(pool->mutex);
    pool->done = uthread_cond_create(pool->mutex);

    for (int i = 0; i < max_threads; i++) {
        pool->threads[i] = uthread_create(worker_thread, pool);
    }
    return pool;
}

/**
 * Sechedule task f(arg) to be executed.
 */
void tpool_schedule_task(tpool_t pool, void (*f)(tpool_t, void *), void *arg) {
    // TODO
    uthread_mutex_lock(pool->mutex);
    
    Node* newTask = malloc(sizeof(Node));
    newTask->f = f;
    newTask->args = arg;
    newTask->next = NULL;

    if (pool->q.start == NULL) {
        pool->q.start = newTask;
        pool->q.end = newTask;
    }
    else {
        pool->q.end->next = newTask;
        pool->q.end = pool->q.end->next; 
    }
    
    
    uthread_cond_signal(pool->available);
    
    uthread_mutex_unlock(pool->mutex);


}

/**
 * Wait (by blocking) until all tasks have completed and thread pool is thus idle
 */
void tpool_join(tpool_t pool) {
    // TODO
    uthread_mutex_lock(pool->mutex);
    pool->flag = 1;
    while (pool->running > 0 || pool->q.start != NULL)
        uthread_cond_wait(pool->done);
    // printf("here1\n");
    fflush(stdout);
    uthread_mutex_unlock(pool->mutex);
    
    // printf("here2\n");

    for (int i = 0; i < pool->max_threads; i++)
        uthread_join(pool->threads[i], NULL);

    // printf("here3\n");

    uthread_cond_destroy(pool->available);
    uthread_cond_destroy(pool->done);
    uthread_mutex_destroy(pool->mutex);
}
