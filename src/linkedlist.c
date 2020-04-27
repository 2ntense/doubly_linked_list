#include "linkedlist.h"

list_t *create_list()
{
    list_t *list = malloc(sizeof(list_t));
    list->head = NULL;
    list->tail = NULL;
    list->size = 0;
    return list;
}

list_t *create_list_val(int data)
{
    list_t *list = create_list();
    list->head = create_node(data, NULL, NULL);
    list->tail = list->head;
    list->size = 1;
    return list;
}

node_t *create_node(int data, node_t *prev_node, node_t *next_node)
{
    node_t *new_node = (node_t *)malloc(sizeof(node_t));
    new_node->data = data;
    new_node->prev = prev_node;
    new_node->next = next_node;
    return new_node;
}

void dll_set_tail(node_t *node, list_t *list)
{
    list->tail = node;
}

int dll_is_empty(list_t *list)
{
    return !(list->size > 0);
}

// can be optimized
node_t *dll_insert(int index, int data, list_t *list)
{
    if (dll_is_empty(list))
    {
        return NULL;
    }

    if (index > list->size)
    {
        return NULL;
    }
    else if (index == 0)
    {
        return dll_prepend(data, list);
    }
    else if (index == list->size)
    {
        return dll_push(data, list);
    }

    node_t *n_ptr = list->head;
    int i = index;
    while (i > 0)
    {
        dll_next_node(&n_ptr);
        i--;
    }
    node_t *insert_node = create_node(data, n_ptr->prev, n_ptr);
    insert_node->prev->next = insert_node;
    n_ptr->prev = insert_node;
    list->size++;
    return insert_node;
}

node_t *dll_append(int data, list_t *list)
{
    return dll_push(data, list);
}

node_t *dll_prepend(int data, list_t *list)
{
    if (list == NULL)
    {
        return NULL;
    }

    if (dll_is_empty(list))
    {
        return dll_push(data, list);
    }

    node_t *new_head = create_node(data, NULL, NULL);
    new_head->next = list->head;
    list->head->prev = new_head;
    list->head = new_head;
    list->size++;
    return new_head;
}

void dll_clear(list_t *list)
{
    if (dll_is_empty(list))
    {
        return;
    }

    node_t *n = list->head;
    node_t *to_free = NULL;

    while (n != NULL)
    {
        to_free = n;
        dll_next_node(&n);
        free(to_free);
        list->size--;
    }

    list->head = NULL;
    list->tail = NULL;
    list->size = 0;
}

void dll_free(list_t *list)
{
    if (list->head != NULL)
    {
        dll_clear(list);
    }
    free(list);
}

void dll_delete_idx(int index, list_t *list)
{
    node_t *n_ptr = list->head;
    for (int i = 0; i < index; i++)
    {
        dll_next_node(&n_ptr);
    }

    if (n_ptr->next == NULL)
    {
        if (n_ptr->prev != NULL)
        {
            n_ptr->prev->next = NULL;
            dll_set_tail(n_ptr->prev, list);
        }
    }
    else
    {
        n_ptr->prev->next = n_ptr->next;
        n_ptr->next->prev = n_ptr->prev;
    }

    free(n_ptr);
    list->size--;
}

void dll_next_node(node_t **n)
{
    *n = (*n)->next;
}

void dll_prev_node(node_t **n)
{
    *n = (*n)->prev;
}

int dll_contains(int val, list_t *list)
{
    if (dll_is_empty(list))
    {
        return INT_MIN;
    }

    int idx = 0;
    node_t *n_ptr = list->head;
    while (n_ptr != NULL)
    {
        if (n_ptr->data == val)
        {
            return idx;
        }
        dll_next_node(&n_ptr);
        idx++;
    }
    return INT_MIN;
}

// can be optimized
int dll_get(int idx, list_t *list)
{
    if (dll_is_empty(list))
    {
        return INT_MIN;
    }

    node_t *n_ptr = list->head;
    for (int i = 0; i < idx; i++)
    {
        dll_next_node(&n_ptr);
    }
    return n_ptr->data;
}

int dll_get_first(list_t *list)
{

    if (list->head != NULL)
    {
        return list->head->data;
    }
    return INT_MIN;
}

int dll_get_last(list_t *list)
{
    if (list->tail != NULL)
    {
        return list->tail->data;
    }
    return INT_MIN;
}

node_t *dll_push(int val, list_t *list)
{
    if (list == NULL)
    {
        return NULL;
    }

    node_t *new_node = create_node(val, NULL, NULL);
    if (dll_is_empty(list))
    {
        list->head = new_node;
        list->tail = new_node;
    }
    else
    {
        new_node->prev = list->tail;
        list->tail->next = new_node;
        dll_set_tail(new_node, list);
    }

    list->size++;
    return new_node;
}

int dll_pop(list_t *list)
{
    if (list == NULL || list->tail == NULL)
    {
        return INT_MIN;
    }

    int ret = list->tail->data;

    if (list->size == 1)
    {
        free(list->tail);
        list->head = NULL;
        list->tail = NULL;
    }
    else
    {
        node_t *new_tail = list->tail->prev;
        list->tail->prev->next = NULL;
        free(list->tail);
        dll_set_tail(new_tail, list);
    }
    list->size--;
    return ret;
}