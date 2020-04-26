#include <stdio.h>

#include "linkedlist.h"

list_t *create_list()
{
    list_t *list = malloc(sizeof(list_t));
    list->head = NULL;
    list->size = 0;
    return list;
}

list_t *create_list_val(int data)
{
    list_t *list = create_list();
    list->head = create_node(data, NULL);
    return list;
}

node_t *create_node(int data, node_t *prev_node)
{
    node_t *new_node = (node_t *)malloc(sizeof(node_t));
    new_node->data = data;
    new_node->prev = prev_node;
    new_node->next = NULL;
    return new_node;
}

int dll_is_empty(list_t *list)
{
    return (list->head == NULL);
}

void dll_insert(int index, int data, list_t *list)
{
    if (index > list->size)
    {
        return;
    }
    else if (index == 0)
    { dll_prepend(data, list);
        return;
    }
    else if (index == list->size)
    {
        dll_append(data, list);
        return;
    }

    node_t *n_ptr = list->head;
    int i = index;
    while (i > 0)
    {
        dll_next_node(&n_ptr);
        i--;
    }
    node_t *insert_node = create_node(data, n_ptr->prev);
    insert_node->next = n_ptr;
    insert_node->prev->next = insert_node;
    n_ptr->prev = insert_node;
    list->size++;
}

void dll_append(int data, list_t *list)
{
    if (list->head == NULL)
    {
        list->head = create_node(data, NULL);
        list->size++;
        return;
    }

    node_t *n_ptr = list->head;
    while (n_ptr->next != NULL)
    {
        dll_next_node(&n_ptr);
    }
    n_ptr->next = create_node(data, n_ptr);
    list->size++;
}

void dll_prepend(int data, list_t *list)
{
    if (dll_is_empty(list) == 1)
    {
        dll_append(data, list);
        return;
    }
    node_t *new_head = create_node(data, NULL);
    new_head->next = list->head;
    list->head->prev = new_head;
    list->head = new_head;
    list->size++;
}
        
void dll_clear(list_t *list)
{
    for (int i = (list->size - 1); i >= 0; i--)
    {
        dll_delete_idx(i, list);
    }
    list->head = NULL;
    list->size = 0;
}

void dll_free(list_t *list)
{
    dll_clear(list);
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
    int index = 0;
    node_t *n_ptr = list->head;
    while (n_ptr != NULL)
    {
        if (n_ptr->data == val)
        {
            return index;
        }
        dll_next_node(&n_ptr);
        index++;
    }
    return -1;
}

int *dll_get(int idx, list_t *list)
{
    node_t *n_ptr = list->head;

    if (n_ptr == NULL)
    {
        return NULL;
    }

    for (int i = 0; i < idx; i++)
    {
        dll_next_node(&n_ptr);
    }
    return &n_ptr->data;
}

int *dll_get_first(list_t *list)
{
    if (list->head != NULL)
    {
        return &list->head->data;
    }
    return NULL;
}

int *dll_get_last(list_t *list)
{
    return dll_get(list->size - 1, list);
}

int main()
{
    list_t *list = (list_t *)malloc(sizeof(list_t));
    list->size = 0;
    
    dll_prepend(777, list);

    return 0;
}