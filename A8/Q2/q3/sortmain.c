#include <stdio.h>
#include <stdlib.h>

#include "int_element.h"
#include "str_element.h"
#include "element.h"
#include "refcount.h"

/* If the string is numeric, return an int_element. Otherwise return a str_element. */
struct element *parse_string(char *str) {
  char *endp;
  /* strtol returns a pointer to the first non-numeric character in endp.
     If it gets to the end of the string, that character will be the null terminator. */
  int value = strtol(str, &endp, 10);
  if(str[0] != '\0' && endp[0] == '\0') {
    /* String was non-empty and strtol conversion succeeded - integer */
    return (struct element *)int_element_new(value);
  } else {
    return (struct element *)str_element_new(str);
  }
}

int cmpfunc (const void * thisvOne,const void * thisvTwo) {
  struct element** thisOne = (struct element**) thisvOne;
  struct element** thisTwo = (struct element**) thisvTwo;
  (*thisOne)->class->compare(*thisOne, *thisTwo);
}

int main(int argc, char **argv) {
  struct element **arr = malloc(sizeof(struct element *) * (argc - 1));

  /* TODO: Read elements into a new array using parse_string */
  for (int i = 0; i < argc - 1; i++) {
    // struct element* e = parse_string(argv[i+1]);
    arr[i] = parse_string(argv[i+1]);
  }

  /* TODO: Sort elements with qsort */
  qsort(arr, argc-1, sizeof(struct element*), cmpfunc);
  
  printf("Sorted: ");
  /* TODO: Print elements, separated by a space */
  for (int i = 0; i < argc - 1; i++) {
    arr[i]->class->print(arr[i]);
    printf(" ");
    rc_free_ref(arr[i]);
  }
  printf("\n");
  free(arr);
}
