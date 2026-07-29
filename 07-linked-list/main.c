#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
  struct Node *next;
  void *data;
} Node;

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

// Takes ownership of `data` only on success; on failure the caller still
// owns `data` and must free it.
Node *list_init(void *data) {
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

// Takes ownership of `data` only on success; on failure the caller still
// owns `data` and must free it.
Node *list_append(Node *head, void *data) {
  if (head == NULL || data == NULL) {
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

Node *list_append_str(Node *head, const char *str) {
  char *data = make_string(str);
  Node *node = list_append(head, data);
  if (node == NULL) {
    free(data);
  }
  return node;
}

int main(void) {

  void *data = make_string("Head (A)");
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
