#ifndef LABA5_CLIST_H
#define LABA5_CLIST_H

#include <stdlib.h>
#include <stdio.h>
#include <iostream>

using namespace std;

#define INFINITY RAND_MAX
#define MATRIX_MAX_SIZE 1000
#define RANGE_ABS_MAX 100

/*
 * Structure of list
 */
typedef struct node
{
    int value;
    struct node *next;
} node_t;

/*
 *  Create new node
 */
node_t *node_create(const int val);

/*
 * Add node as first element to list
 */
node_t *list_add_first(node_t *node, node_t *head);

/*
 * Free memory list
 */
void list_free(node_t *head);

/*
 * Print list value
 */
void list_print(const node_t *head);

/*
 * Create copy of list
 */
node_t *list_copy(node_t *head);

#endif
