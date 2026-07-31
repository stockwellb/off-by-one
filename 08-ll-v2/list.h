#ifndef LIST_H
#define LIST_H

#include <stddef.h>

/*
 * Singly linked list.
 *
 * A list is a `Node *`. NULL is the empty list -- there is no
 * constructor and nothing to free:
 *
 *     Node *head = NULL;                              // valid empty list
 *     list_splice(&head, create_node(x));             // prepend
 *     list_splice(list_end(&head), create_node(y));   // append
 *     free_node(list_unsplice(list_at(&head, 2)));    // delete index 2
 *
 * A `Node **` is a *link*: the address of the pointer that points at a
 * node. That is either &head or &some_node->next. Because those are the
 * same kind of thing, no operation needs a special case for the head.
 *
 * The finders locate a link; the splicers mutate one. Neither allocates.
 *
 * Ownership:
 *   Nodes  -- caller allocates (create_node) and frees (free_node).
 *             list_unsplice detaches a node but does not free it.
 *   data   -- borrowed. The list never reads, copies, or frees it.
 *             It must outlive the node holding it.
 *
 * Indices are 0-based. A list of length n has n valid element indices
 * (0..n-1) and n+1 valid insert positions (0..n).
 *
 * A NULL link is a programming error and trips an assert. A link whose
 * *value* is NULL is a legal empty position -- the end of a list.
 */

typedef struct Node {
  void *data;
  struct Node *next;
} Node;

/* Insert `node` at `link`. O(1). */
void list_splice(Node **link, Node *node);

/* Detach and return the node at `link`, or NULL if the position is
   empty. Does not free. O(1). */
Node *list_unsplice(Node **link);

/* Link at `index`, or NULL if index > length. O(n). */
Node **list_at(Node **head, size_t index);

/* Link at the end of the list -- always valid, holds NULL. O(n). */
Node **list_end(Node **head);

/* Allocation. The four functions above never call these. Nodes come
   in from the caller and go out to the caller. */
Node *list_create_node(void *data); /* NULL on allocation failure */

void list_free_node(Node *node); /* safe on NULL */

#endif // LIST_H
