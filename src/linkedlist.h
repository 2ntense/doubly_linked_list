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

extern list_t *dll_new_list(void);
extern node_t *dll_new_node(int data, node_t *prev_node , node_t *next_node);
extern int dll_is_empty(list_t *list);
extern node_t *dll_insert(int index, int data, list_t *list);
extern node_t *dll_append(int data, list_t *list);
extern node_t *dll_prepend(int data, list_t *list);
extern int dll_contains(int data, list_t *list);
extern int dll_get(int index, list_t *list);
extern int dll_get_first(list_t *list);
extern int dll_get_last(list_t *list);
extern void dll_free_list(list_t *list);
extern void dll_free_node(node_t *node);
extern void dll_delete_idx(int index, list_t *list);
extern node_t *dll_push(int data, list_t *list);
extern int dll_pop(list_t *list);
extern void dll_clear(list_t *list);

#endif