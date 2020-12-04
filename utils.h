#ifndef UTILS_H
#define UTILS_H

typedef struct {
  char *string;  // change here for different data types
  size_t length;
} data_t;

struct llqueue { // queue to store strings read in
  data_t *item;
  struct llqueue *next;
};

int string_cmp(void *str1, void *str2);
int int_cmp(void *int1, void *int2);
char *read_strings(int size);
int read_words(struct llqueue **queue);
void destroy_queue(struct llqueue **queue);

#endif
