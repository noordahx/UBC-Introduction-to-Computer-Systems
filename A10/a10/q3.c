#include <stdlib.h>
#include <stdio.h>
#include "uthread.h"
#include "uthread_mutex_cond.h"

#define NUM_THREADS 3
uthread_t threads[NUM_THREADS];
uthread_mutex_t mx;
uthread_cond_t aCond;
int lock = 0;

void randomStall() {
  int i, r = random() >> 16;
  while (i++<r);
}

void waitForAllOtherThreads() {
  uthread_mutex_lock(mx);
    while(lock != NUM_THREADS) {
      uthread_cond_wait(aCond);
    }
  uthread_mutex_unlock(mx);
}

void* p(void* v) {
  randomStall();
  
  uthread_mutex_lock(mx);
    lock++;
    printf("a\n");
    uthread_cond_broadcast(aCond);
  uthread_mutex_unlock(mx);

  waitForAllOtherThreads();

  printf("b\n");
  return NULL;
}

int main(int arg, char** arv) {
  uthread_init(4);
  
  mx = uthread_mutex_create();
  aCond = uthread_cond_create(mx);
  lock = 0;
  
  for (int i=0; i<NUM_THREADS; i++)
    threads[i] = uthread_create(p, NULL);
  for (int i=0; i<NUM_THREADS; i++)
    uthread_join (threads[i], NULL);
  printf("------\n");
}