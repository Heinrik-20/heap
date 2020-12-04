#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "heap.h"

/* Initialized heap */
heap_t *init_heap(int nelem, int cmp(void *, void *)){
  heap_t *new = (heap_t *)malloc(sizeof(heap_t));
  assert(new);
  new->heap = (node_t **)malloc(sizeof(node_t *) * nelem);
  assert(new->heap);
  new->cmp = cmp;
  return new;
}

/* Returns allocated memory for heap */
void destroy_heap(heap_t *heap, int nelem){
  for (int i = 0;i < nelem;i++){
    free((heap->heap)[i]);
    (heap->heap)[i] = NULL;
  }
  free(heap->heap);
  heap->heap = NULL;
  free(heap);
  heap = NULL;
  return;
}

/* Inserting strings into heap */
heap_t *insert_heap(heap_t *heap, void *value, int index){
  (heap->heap)[index] = (node_t *)malloc(sizeof(node_t));
  assert((heap->heap)[index]);
  ((heap->heap)[index])->data = value;
  heapify(heap, (size_t)(index + 1));
  return heap;
}

/* Turns the array into a heap, via a downheap method */
void heapify(heap_t *heap, size_t nelem){
  int mid = (int)nelem / 2;
	for (int i = mid;i >= 0;i--){
		downheap(heap, i, nelem);
	}
	return;
}

void downheap(heap_t *heap, int parent, size_t nelem){
  int left = parent * 2 + 1;
	int right = 2 * parent + 2;
	int swap_idx = parent;
	if (left < nelem){
		if ((heap->cmp)(((heap->heap)[left])->data, ((heap->heap)[swap_idx])->data) > 0){
			swap_idx = left;
		}
    /*if ((heap->cmp)(((heap->heap)[left])->priority, ((heap->heap)[swap_idx])->priority) > 0){
			swap_idx = left;
		}*/
	}
	if (right < nelem){
		if ((heap->cmp)(((heap->heap)[right])->data, ((heap->heap)[swap_idx])->data) > 0){
			swap_idx = right;
		}
    /*if ((heap->cmp)(((heap->heap)[right])->priority, ((heap->heap)[swap_idx])->priority) > 0){
			swap_idx = left;
		}*/
	}
	if (parent == swap_idx) return;
	swap(&(heap->heap)[parent], &(heap->heap)[swap_idx]);
	downheap(heap, swap_idx, nelem);
}

/* Swap positions of two items in an array */
void swap(node_t **item1, node_t **item2){
	node_t *temp = *item2;
	*item2 = *item1;
	*item1 = temp;
	return;
}

/* Gets the top most item in the heap */
node_t *get_root(heap_t *heap, size_t nelem){
  swap(&(heap->heap)[0], &(heap->heap)[nelem - 1]);
  heapify(heap, nelem - 1);
  return (heap->heap)[nelem - 1];
}

/* Sorts the heap */
void heap_sort(heap_t *heap, size_t nelem){
	if ((int)nelem == 1){
		return;
	}
	heapify(heap, nelem);
	swap(&((heap->heap)[0]), &((heap->heap)[nelem - 1]));
	return heap_sort(heap, nelem - 1);
}
