#include "list.h"
#include <stdio.h>
#include <stdlib.h>

int main(void) {
  int data[5] = {10, 11, 12, 13, 14};
  Node *head = NULL;

  Node *alpha = list_node_create(&data[0]);
  Node *beta = list_node_create(&data[1]);
  Node *charlie = list_node_create(&data[2]);
  Node *delta = list_node_create(&data[3]);
  Node *echo = list_node_create(&data[4]);

  list_splice(&head, alpha);
  list_splice(list_end(&head), beta);
  list_splice(list_end(&head), charlie);
  list_splice(list_end(&head), delta);
  list_splice(list_end(&head), echo);

  printf("List len: %ld\n", list_len(head));

  Node **selected_alpha = list_at(&head, 0);
  Node **selected_echo = list_at(&head, 4);

  printf("Alpha data: %d\n", *(int *)(*selected_alpha)->data);
  printf("Echo  data: %d\n", *(int *)(*selected_echo)->data);
  return EXIT_SUCCESS;
}
