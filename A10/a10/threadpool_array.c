#include <stdlib.h>
#include "uthread.h"
#include "uthread_mutex_cond.h"
#include "threadpool.h"
#define TASK_QUEUE_SIZE 100

// struct Node {
//     void(*f)(tpool_t, void*);
//     void* args;
//     Node *next;
// }

// struct Queue {

// }


struct tpool {
    // TODO
    unsigned int max_threads;
    unsigned int running;

    struct {
        void (*f)(tpool_t, void*);
        void *args;
    } taskList[TASK_QUEUE_SIZE];
    unsigned int first_task;
    unsigned int next_task;
    unsigned int num_tasks;
    
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
    
        while (pool->num_tasks == 0) 
            uthread_cond_wait(pool->available);

        void(*f)(tpool_t, void*) = pool->taskList[pool->first_task].f;
        void(*args) = pool->taskList[pool->first_task].args;
        pool->first_task = (pool->first_task + 1) % TASK_QUEUE_SIZE;
        pool->num_tasks--;
        
        pool->running++;

        uthread_mutex_unlock(pool->mutex);

        f(pool, args);

        uthread_mutex_lock(pool->mutex);

        pool->running--;

        if (pool->running ==0 && pool->num_tasks == 0)
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
    tpool_t pool = malloc(sizeof(tpool_t));

    pool->max_threads = max_threads;
    pool->running = 0;
    pool->next_task = 0;
    pool->num_tasks = 0;
    pool->first_task = 0;
    pool->threads = malloc(max_threads * sizeof(uthread_t));
    pool->mutex = uthread_mutex_create();
    pool->available = uthread_cond_create(pool->mutex);
    pool->done = uthread_cond_create(pool->mutex);

    for (int i = 0; i < max_threads; i++)
        pool->threads[i] = uthread_create(worker_thread, pool);
    
    return pool;
}

/**
 * Sechedule task f(arg) to be executed.
 */
void tpool_schedule_task(tpool_t pool, void (*f)(tpool_t, void *), void *arg) {
    // TODO
    uthread_mutex_lock(pool->mutex);
    pool->taskList[pool->next_task].f = f;
    pool->taskList[pool->next_task].args = arg;
    pool->next_task = (pool->next_task + 1) % TASK_QUEUE_SIZE;
    pool->num_tasks++;
    
    uthread_cond_signal(pool->available);
    
    uthread_mutex_unlock(pool->mutex);


}

/**
 * Wait (by blocking) until all tasks have completed and thread pool is thus idle
 */
void tpool_join(tpool_t pool) {
    // TODO
    uthread_mutex_lock(pool->mutex);
    
    while (pool->running > 0 || pool->num_tasks > 0)
        uthread_cond_wait(pool->done);

    // for (int i = 0; i < pool->max_threads; i++)
    //     uthread_join(pool->threads[i], NULL);
    

    uthread_mutex_unlock(pool->mutex);
    
}
