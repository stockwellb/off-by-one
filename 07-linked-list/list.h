#ifndef LIST_H
#define LIST_H

#include <stdbool.h>
#include <stddef.h>

typedef struct Node {
  struct Node *next;
  void *data;
} Node;

Node *list_init(void *data);
void list_destroy(Node *head);
bool list_append(Node *head, void *data);
void list_delete_node(Node **head, Node *target);
void list_delete_at(Node **head, size_t index);
void *list_remove_at(Node **head, size_t index);
void list_print(Node *head);

#endif // LIST_H
/*
#3 — list_remove_at, transfers ownership

void *list_remove_at(Node **head, size_t index);  //unlinks + frees node ONLY,
returns data; caller frees it

Here's a nice payoff from your assert(data != NULL) invariant: since data in the
list is never NULL, NULL is an unambiguous "index out of range" sentinel for the
return. No out-param needed.

Internally you'll want a shared helper — both delete_atand remove_at are "unlink
node at index, return it (or NULL)"; the only difference is delete_at then
callsfree_node while remove_at frees just the node and returns node->data.
Something like:

static Node *unlink_at(Node **head, size_t index);  //walks, relinks, returns
unlinked node or NULL

That keeps the walk-and-relink logic in one place instead of duplicated.

One open call: out-of-bounds policy — silent no-op /NULL (current style) vs
assert. Since this is learning code and you've been asserting on the input
contract,asserting index bounds is defensible too. Your pick.
*/
