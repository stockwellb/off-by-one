#include "list.h"
#include <assert.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Node *list_init(void *data) {
  assert(data != NULL);
  Node *node = malloc(sizeof(Node));

  if (node == NULL) {
    return NULL;
  }

  node->data = data;
  node->next = NULL;

  return node;
}

void list_destroy(Node *head) {
  Node *current = head;

  while (current != NULL) {
    Node *next = current->next;
    if (current->data != NULL) {
      free(current->data);
    }
    printf("destroying: %p\n", (void *)current);
    free(current);
    current = next;
  }
}

Node *list_append(Node *head, void *data) {
  assert(data != NULL);
  if (head == NULL) {
    return NULL;
  }
  Node *node = malloc(sizeof(Node));
  if (node == NULL) {
    return NULL;
  }
  node->next = NULL;
  node->data = data;

  Node *current = head;

  while (current->next != NULL) {
    current = current->next;
  }

  current->next = node;
  return node;
}

void list_delete_node(Node **head, Node *target) {
  if (head == NULL || *head == NULL || target == NULL) {
    return;
  }

  Node *ref = *head;

  // delete the head;
  if (ref == target) {
    *head = ref->next;

    if (ref->data != NULL) {
      free(ref->data);
    }

    printf("deleting: %p\n", (void *)ref);
    free(ref);
    return;
  }

  while (ref != NULL && ref->next != target) {
    ref = ref->next;
  }

  if (ref == NULL) {
    return;
  }

  ref->next = target->next;

  if (target->data != NULL) {
    free(target->data);
  }

  printf("deleting: %p\n", (void *)target);
  free(target);
}
