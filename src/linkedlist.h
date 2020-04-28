#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <stdlib.h>
#include <limits.h>

typedef struct node node_t;
struct node
{
    int data;
    node_t *prev;
    node_t *next;
};

typedef struct list list_t;
struct list
{
    size_t size;
    node_t *head;
    node_t *tail;
};

extern list_t *dll_new_list();
// extern list_t *dll_new_list(int data);
extern node_t *dll_new_node(int, node_t *, node_t *);
extern int dll_is_empty(list_t *);
extern node_t *dll_insert(int, int, list_t *);
extern node_t *dll_append(int, list_t *);
extern node_t *dll_prepend(int, list_t *);
extern int dll_contains(int, list_t *);
extern int dll_get(int, list_t *);
extern int dll_get_first(list_t *);
extern int dll_get_last(list_t *);
extern void dll_free(list_t *);
extern void dll_delete_idx(int, list_t *);
extern node_t *dll_push(int, list_t *);
extern int dll_pop(list_t *);
extern void dll_clear(list_t *);

#endif