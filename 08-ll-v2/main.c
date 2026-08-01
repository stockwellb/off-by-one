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
  int *value_five = (int *)list_get_at(list, 4);

  printf("item one  : %d\n", *value_one);
  printf("item five : %d\n", *value_five);

  int *value_three = (int *)list_remove_at(list, 2);

  printf("item three: %d\n", *value_three);

  printf("List len: %ld\n", list_len(list));

  return EXIT_SUCCESS;
}
