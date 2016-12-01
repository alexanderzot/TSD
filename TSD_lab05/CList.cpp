#include "CList.h"

node_t *node_create(const int val)
{
    node_t *tmp = new node_t;
    if (tmp)
    {
        tmp->value = val;
        tmp->next = NULL;
    }
    return tmp;
}

node_t *list_add_first(node_t *node, node_t *head)
{
    if (!head)
        return node;
    node->next = head;
    head = node;
    return head;
}

void list_free(node_t *head)
{
    node_t *next = NULL;
    while (head)
    {
        next = head->next;
        delete head;
        head = next;
    }
}

void list_print(const node_t *head)
{
    node_t *tmp = (node_t *)head;
    do
    {
        cout << tmp->value << " ";
        tmp = tmp->next;
    }
    while (tmp);
}

node_t *list_copy(node_t *head)
{
    if(!head)
        return NULL;
    node_t* first = node_create(head->value);
    node_t* last = NULL;
    node_t* prev = first;
    for (node_t *tmp = head->next; tmp; tmp = tmp->next)
    {
        last = node_create(tmp->value);
        prev->next = last;
        prev = prev->next;
    }
    return first;
}