#include "list.h"
#include <assert.h>
#include <stddef.h>
#include <stdlib.h>

void list_splice(Node **link, Node *node) {
  assert(link != NULL);
  assert(node != NULL);
  node->next = *link;
  *link = node;
}

Node *list_unsplice(Node **link) {
  assert(link != NULL);
  Node *node = *link;
  if (node != NULL) {
    *link = node->next;
  }
  return node;
}

Node **list_end(Node **head) {
  assert(head != NULL);
  Node **link = head;
  while (*link != NULL) {
    link = &(*link)->next;
  }
  return link;
}

Node **list_at(Node **head, size_t index) {
  assert(head != NULL);
  Node **link = head;
  for (size_t i = 0; i < index; i++) {
    if (*link == NULL) {
      return NULL;
    }
    link = &(*link)->next;
  }
  return link;
}
size_t list_len(const Node *head) {
  size_t count = 0;
  for (const Node *cur = head; cur != NULL; cur = cur->next)
    count++;
  return count;
}

Node *list_node_create(void *data) {
  Node *node = malloc(sizeof(Node));
  if (node == NULL) {
    return NULL;
  }
  node->data = data;
  node->next = NULL;
  return node;
}

void list_node_free(Node *node) {
  free(node); // free(NULL) is a no-op, so this is safe
}
