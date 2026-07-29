#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
  struct Node *next;
  void *data;
} Node;

Node *list_init(void) {
  Node *e = malloc(sizeof(Node));
  Node *d = malloc(sizeof(Node));
  Node *c = malloc(sizeof(Node));
  Node *b = malloc(sizeof(Node));
  Node *a = malloc(sizeof(Node));

  if (!a || !b || !c || !d || !e) {
    return NULL;
  }

  *e = (Node){.next = NULL, .data = NULL};
  *d = (Node){.next = e, .data = NULL};
  *c = (Node){.next = d, .data = NULL};
  *b = (Node){.next = c, .data = NULL};
  *a = (Node){.next = b, .data = NULL};

  return a;
}

void list_destroy(Node *head) {
  Node *current = head;

  while (current != NULL) {
    Node *next = current->next;
    free(current);
    printf("destroyed: %p\n", (void *)current);
    current = next;
  }
}

void list_delete_node(Node **head, Node *target) {
  if (*head == NULL || head == NULL || target == NULL) {
    return;
  }

  Node *ref = *head;

  // delete the head;
  if (ref == target) {
    *head = ref->next;
    free(ref);
    printf("deleted: %p\n", (void *)ref);
    return;
  }

  while (ref != NULL && ref->next != target) {
    ref = ref->next;
  }

  if (ref == NULL) {
    return;
  }

  ref->next = target->next;

  free(target);
  printf("deleted: %p\n", (void *)target);
}

int main(void) {
  Node *head = list_init();
  Node *current = head;

  while (current != NULL) {
    printf("address: %p\n", (void *)current);
    current = current->next;
  }

  Node *target = head->next->next->next;
  list_delete_node(&head, target);

  list_destroy(head);
  printf("Done!\n");
}
