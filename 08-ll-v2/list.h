#ifndef LIST_H
#define LIST_H

#include <stdbool.h>
#include <stddef.h>

typedef struct List List;

List *list_create(void);
void list_destroy(List *list);
bool list_push(List *list, void *data);
void *list_get_at(const List *list, size_t index);
void *list_remove_at(List *list, size_t index);
void list_delete_at(List *list, size_t index);
size_t list_len(const List *list);

#endif // LIST_H
