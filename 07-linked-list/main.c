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

Node *list_append_str(Node *head, const char *str) {
  char *data = make_string(str);
  if (data == NULL) {
    return NULL;
  }
  Node *node = list_append(head, data);
  if (node == NULL) {
    free(data);
  }
  return node;
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

  Node *current = head;

  while (current != NULL) {
    printf("address: %p, data:%s\n", (void *)current, (char *)current->data);
    current = current->next;
  }

  Node *target = head->next->next->next;
  list_delete_node(&head, target);

  list_destroy(head);
  printf("Done!\n");

  return EXIT_SUCCESS;
}
