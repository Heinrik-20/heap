#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "utils.h"

#define MAX_CHAR 100

/* Comparison functions */  // put in more functions if need be
int string_cmp(void *str1, void *str2){
  char *s1 = (char *)str1, *s2 = (char *)str2;
  return strcmp(s1, s2);
}

int int_cmp(void *int1, void *int2){
  int *i1 = (int *)int1, *i2 = (int *)int2;
  return (*i1 - *i2);
}

/* For reading in strings from stdin */
char *read_strings(int size){
	char *string = (char *)malloc(sizeof(char) * size);
	int c, index = 0, curr_size = MAX_CHAR;
	while (((c = getchar()) != '\r') && (c != '\n') && (c != EOF)){
		if (index >= curr_size){
			string = (char *)realloc(string,
				sizeof(char) * (curr_size + curr_size));
			assert(string);
			curr_size *= 2;
		}
		string[index] = c;
		index += 1;
	}
	string[index] = '\0';
	if (c == EOF){
		free(string);
		string = NULL;
	}
	return string;
}

/* for reading multiple strings, using the read_strings function, returns
   number of stirngs read in */
int read_words(struct llqueue **queue){
  int nelem = 0;
  char *word = NULL;
  while ((word = read_strings(MAX_CHAR)) != NULL){
    struct llqueue *new = (struct llqueue *)malloc(sizeof(struct llqueue));
    data_t *data = (data_t *)malloc(sizeof(data_t));
    assert(data && new);
    nelem += 1;
    data->length = strlen(word);
    data->string = (char *)malloc(sizeof(char) * ((data->length) + 1));
    strcpy(data->string, word);
    new->item = data;
    free(word);
    if (*queue) {
      new->next = *queue;
      *queue = new;
    }
    else {
      *queue = new;
      new->next = NULL;
    }
  }
  return nelem;
}

/* Returns allocated memory for queue */
void destroy_queue(struct llqueue **queue){
  struct llqueue *temp = *queue, *prev = NULL;
  while (temp){
    prev = temp;
    temp = temp->next;
    free(prev->item->string);
    prev->item->string = NULL;
    free(prev->item);
    prev->item = NULL;
    free(prev);
    prev = NULL;
  }
  return;
}
