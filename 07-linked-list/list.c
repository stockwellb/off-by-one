#include "list.h"
#include <assert.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void free_node(Node *node) {
  free(node->data);
  free(node);
}

static Node *create_node(void *data) {
  Node *node = malloc(sizeof(Node));
  if (node == NULL) {
    return NULL;
  }

  node->next = NULL;
  node->data = data;
  return node;
}

// Takes ownership of `data` only on success; on failure the caller still
// owns `data` and must free it.
Node *list_init(void *data) {
  assert(data != NULL);
  return create_node(data);
}

void list_destroy(Node *head) {
  Node *current = head;

  while (current != NULL) {
    Node *next = current->next;
    free_node(current);
    current = next;
  }
}

// Takes ownership of `data` only on success; on failure the caller still
// owns `data` and must free it.
bool list_append(Node *head, void *data) {
  assert(data != NULL);
  if (head == NULL) {
    return false;
  }
  Node *node = create_node(data);
  if (node == NULL) {
    return false;
  }

  Node *current = head;

  while (current->next != NULL) {
    current = current->next;
  }

  current->next = node;
  return true;
}

void list_delete_at(Node **head, size_t index) {
  if (head == NULL)
    return;

  Node **link = head; // the pointer that points AT the current node
  for (size_t i = 0; i < index; i++) {
    if (*link == NULL)
      return; // index past the end
    link = &(*link)->next;
  }
  if (*link == NULL)
    return; // index == length

  Node *victim = *link;
  *link = victim->next;
  free_node(victim);
}

void list_print(Node *head) {
  Node *current = head;

  while (current != NULL) {
    printf("address: %p, data:%s\n", (void *)current, (char *)current->data);
    current = current->next;
  }
}
