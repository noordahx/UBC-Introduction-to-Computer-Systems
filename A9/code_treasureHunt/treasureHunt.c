#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/errno.h>
#include <assert.h>
#include "uthread.h"
#include "queue.h"
#include "disk.h"

queue_t pending_read_queue;
volatile int pending_reads;
int toSearch;
int temp;

void interrupt_service_routine() {
  // TODO
  void *val, *arg;
  void (*callback) (void*, void*);
  queue_dequeue(pending_read_queue, &val, &arg, &callback);
  callback(val, arg);
}

void handleOtherReads(void *resultv, void *countv) {
  // TODO
  toSearch = *((int*)resultv);
  (*(int*)countv)--;
  //printf("%d \n - temp", *(int*)countv);
  if (*(int*)countv >= 0) {
    queue_enqueue(pending_read_queue, resultv, countv, handleOtherReads);
    disk_schedule_read(resultv, toSearch);
  }
    
}

void handleFirstRead(void *resultv, void *countv) {
  // TODO
  toSearch = *((int*)resultv);
  *(int*)countv = *((int*)resultv);
  queue_enqueue(pending_read_queue, resultv, countv, handleOtherReads);
  disk_schedule_read(resultv, toSearch);
}

int main(int argc, char **argv) {
  // Command Line Arguments
  static char* usage = "usage: treasureHunt starting_block_number";
  int starting_block_number;
  char *endptr;
  if (argc == 2)
    starting_block_number = strtol (argv [1], &endptr, 10);
  if (argc != 2 || *endptr != 0) {
    printf ("argument error - %s \n", usage);
    return EXIT_FAILURE;
  }

  // Initialize
  uthread_init (1);
  disk_start (interrupt_service_routine);
  pending_read_queue = queue_create();

  // Start the Hunt
  // TODO
  int value, count = 1;
  queue_enqueue(pending_read_queue, &value, &count, handleFirstRead);
  disk_schedule_read(&value, starting_block_number);
  
  while (count) {} // infinite loop so that main doesn't return before hunt completes
  printf("%d",value);
}
