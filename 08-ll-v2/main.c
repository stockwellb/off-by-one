#include "list.h"
#include <stdio.h>
#include <stdlib.h>

int main(void) {
  int data[5] = {10, 11, 12, 13, 14};
  int data_len = sizeof(data) / sizeof(int);

  List *list = list_create();

  for (int i = 0; i < data_len; i++) {

    list_push(list, &data[i]);
  }

  printf("List len: %ld\n", list_len(list));

  int *value_one = (int *)list_get_at(list, 0);
  int *value_four = (int *)list_get_at(list, 4);

  printf("item one : %d\n", *value_one);
  printf("item four: %d\n", *value_four);
  return EXIT_SUCCESS;
}
