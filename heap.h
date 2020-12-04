#ifndef HEAP_H
#define HEAP_H

typedef struct {
  void *data;
  int priority; // if needed to indicate its importance
} node_t;

typedef struct {
  node_t **heap;
  int (*cmp) (void*, void*);
} heap_t;

heap_t *init_heap(int nelem, int cmp(void *, void *));
void destroy_heap(heap_t *heap, int nelem);
heap_t *insert_heap(heap_t *heap, void *value, int index);
void heapify(heap_t *heap, size_t nelem);
void downheap(heap_t *heap, int parent, size_t nelem); // changes may need to be made here if you are using priority 
void swap(node_t **item1, node_t **item2);
node_t *get_root(heap_t *heap, size_t nelem);
void heap_sort(heap_t *heap, size_t size);

#endif
