#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "heap.h"
#include "utils.h"

/* This program will use a linked list queue to store strings read in
from stdin. The strings will then be transfered into the heap and then
sorted there. */

int main(int argc, char **argv){
  heap_t *heap1 = NULL;
  struct llqueue *queue = NULL, *head = NULL;
  int nelem = 0;
  nelem = read_words(&queue);
  head = queue;
  heap1 = init_heap(nelem, string_cmp);
  for (int i = 0;i < nelem;i++){
    heap1 = insert_heap(heap1, (void*)queue->item->string, i);
    queue = queue->next;
  }
  printf("Before sorting:\n");
  printf("%s", (char *)(((heap1->heap)[0])->data));
  for (int i = 1;i < nelem;i++){
    printf(" %s", (char *)(((heap1->heap)[i])->data));
  }
  printf("\n");
  heap_sort(heap1, nelem);
  printf("After sorting:\n");
  printf("%s", (char *)(((heap1->heap)[0])->data));
  for (int i = 1;i < nelem;i++){
    printf(" %s", (char *)(((heap1->heap)[i])->data));
  }
  printf("\n");
  destroy_heap(heap1, nelem);
  destroy_queue(&head);
  return 0;
}
