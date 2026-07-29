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

Node *list_init(void) {
  Node *e = malloc(sizeof(Node));
  Node *d = malloc(sizeof(Node));
  Node *c = malloc(sizeof(Node));
  Node *b = malloc(sizeof(Node));
  Node *a = malloc(sizeof(Node));

  if (!a || !b || !c || !d || !e) {
    return NULL;
  }

  *e = (Node){.next = NULL, .data = make_string("Node E")};
  *d = (Node){.next = e, .data = make_string("Node D")};
  *c = (Node){.next = d, .data = make_string("Node C")};
  *b = (Node){.next = c, .data = make_string("Node B")};
  *a = (Node){.next = b, .data = make_string("Node A ")};

  return a;
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

int main(void) {
  Node *head = list_init();
  Node *current = head;

  while (current != NULL) {
    printf("address: %p, data:%s\n", (void *)current, (char *)current->data);
    current = current->next;
  }

  Node *target = head->next->next->next;
  list_delete_node(&head, target);

  list_destroy(head);
  printf("Done!\n");
}
