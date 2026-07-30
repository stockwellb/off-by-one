#ifndef LIST_H
#define LIST_H

#include <stddef.h>

typedef struct Node {
  struct Node *next;
  void *data;
} Node;

// Takes ownership of `data` only on success; on failure the caller still
// owns `data` and must free it.
Node *list_init(void *data);

void list_destroy(Node *head);

// Takes ownership of `data` only on success; on failure the caller still
// owns `data` and must free it.
Node *list_append(Node *head, void *data);

void list_delete_node(Node **head, Node *target);

#endif // LIST_H
