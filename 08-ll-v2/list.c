#include "list.h"
#include <assert.h>
#include <stddef.h>
#include <stdlib.h>

typedef struct Node {
  void *data;
  struct Node *next;
} Node;

struct List {
  Node *head;
  Node *tail;
  size_t len;
};

static Node *unsplice(Node **link) {
  assert(link != NULL);
  Node *node = *link;
  if (node != NULL) {
    *link = node->next;
  }
  return node;
}

static Node **node_at(Node **head, size_t index) {
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

static const Node *node_ref_at(const Node *head, size_t index) {
  assert(head != NULL);
  const Node *link = head;
  for (size_t i = 0; i < index; i++) {
    if (link == NULL) {
      return NULL;
    }
    link = link->next;
  }
  return link;
}

static Node *create_node(void *data) {
  Node *node = malloc(sizeof(Node));
  if (node == NULL) {
    return NULL;
  }
  node->data = data;
  node->next = NULL;
  return node;
}

static void free_node(Node *node) {
  free(node); // free(NULL) is a no-op, so this is safe
}

List *list_create(void) {
  List *list = malloc(sizeof(struct List));
  if (list == NULL) {
    return NULL;
  }

  list->head = NULL;
  list->tail = NULL;
  list->len = 0;

  return list;
}

void list_destroy(List *list) {
  if (list == NULL) {
    return;
  }

  Node *current = list->head;
  while (current != NULL) {
    Node *next = current->next;
    free_node(current);
    current = next;
  }
  free(list);
}

bool list_push(List *list, void *data) {
  // create a new node;
  Node *node = create_node(data);
  if (node == NULL) {
    return false;
  }

  // append the node to the tail or the head if there is no tail
  if (list->tail == NULL) {
    list->head = node;
  } else {
    list->tail->next = node;
  }

  // node is always the new tail;
  list->tail = node;
  // track the new length;
  list->len++;
  return true;
}

void *list_get_at(const List *list, size_t index) {
  if (list->head == NULL) {
    return NULL;
  }

  if (index >= list->len) {
    return NULL;
  }
  const Node *node = node_ref_at(list->head, index);
  return node->data;
}

void *list_remove_at(List *list, size_t index);
void list_delete_at(List *list, size_t index);

size_t list_len(const List *list) { return list->len; }
