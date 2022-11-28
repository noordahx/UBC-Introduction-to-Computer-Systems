#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <sys/errno.h>
#include <assert.h>
#include "queue.h"
#include "disk.h"
#include "uthread.h"

queue_t      pending_read_queue;
unsigned int sum = 0;

void interrupt_service_routine () {
  // TODO
  void* val;
  void* arg;
  queue_dequeue(pending_read_queue, &val, &arg, NULL);
  sum+=*(int*)val;
  free(val);
  uthread_unblock(*(uthread_t*)arg);
}


void* read_block (void* blocknov) {
  // TODO schedule read and the update (correctly)
  //printf("here\n");
  int *disk_value = malloc(sizeof(int));
  uthread_t temp_thread = uthread_self();
  queue_enqueue(pending_read_queue, disk_value, (void*)&temp_thread, NULL);
  disk_schedule_read(disk_value, *(int*)blocknov);
  uthread_block();
  free(blocknov);
  return NULL;
}

int main (int argc, char** argv) {

  // Command Line Arguments
  static char* usage = "usage: tRead num_blocks";
  int num_blocks;
  char *endptr;
  if (argc == 2)
    num_blocks = strtol (argv [1], &endptr, 10);
  if (argc != 2 || *endptr != 0) {
    printf ("argument error - %s \n", usage);
    return EXIT_FAILURE;
  }

  // Initialize
  uthread_init (1);
  disk_start (interrupt_service_routine);
  pending_read_queue = queue_create();

  // Sum Blocks
  // TODO
  uthread_t t[num_blocks];
  for (int blockno = 0; blockno < num_blocks; blockno++) {
    int *temp_block_no = malloc(sizeof(int));
    *temp_block_no = blockno;
    t[blockno] = uthread_create(read_block, temp_block_no);
  }

  for (int blockno = 0; blockno < num_blocks; blockno++) {
    uthread_join(t[blockno], 0);
  }

  printf("%d",sum);
}

