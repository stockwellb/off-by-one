#include "list.h"
#include <assert.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void *make_string(const char *src) {
  if (src == NULL) {
    return NULL;
  }

  size_t len = strlen(src) + 1;
  char *dest = malloc(len);

  if (dest != NULL) {
    memcpy(dest, src, len);
  }

  return dest;
}

void list_append_str(Node *head, const char *str) {
  char *data = make_string(str);
  if (data == NULL) {
    return;
  }
  if (list_append(head, data) == false) {
    free(data);
  }
  return;
}

int main(void) {

  void *data = make_string("Head (A)");
  if (data == NULL) {
    return EXIT_FAILURE;
  }

  Node *head = list_init(data);

  if (head == NULL) {
    free(data);
    return EXIT_FAILURE;
  }

  list_append_str(head, "Node B");
  list_append_str(head, "Node C");
  list_append_str(head, "Node D");
  list_append_str(head, "Node E");
  list_append_str(head, "Node F");

  list_print(head);
  list_delete_at(&head, 3);
  list_print(head);

  list_destroy(head);

  printf("Done!\n");

  return EXIT_SUCCESS;
}
