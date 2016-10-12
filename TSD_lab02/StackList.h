#ifndef STACKLIST_H_INCLUDED
#define STACKLIST_H_INCLUDED

#include <iostream>
#include <stdio.h>
#include <stdlib.h>

typedef float type_t;
#define FREE_BEGIN_SIZE 128

#define SL_EMPTY 4
#define SL_MEM_ERROR 3
#define SL_MAX_COUNT 2
#define SL_ERROR 1
#define SL_SUCCESS 0

typedef struct node
{
    type_t value;
    struct node *next;
} node_t;

class StackList
{
private:
    // head list
    node_t *head;
    size_t max_size;
    size_t cur_size;
    // array free memory of node_t *
    const node_t **free_mem;
    size_t free_size;
    size_t free_pos;
    int add_free(const node_t *adr);
    void del_free(const node_t *adr);
    int free_act;
public:
    StackList(const size_t max_size = 10);
    ~StackList();
    int push(const type_t value);
    int pop(type_t *value);
    node_t *get_head(void);
    void print(void);
    void print_free(void);
    void free_switch(void);
};

#endif // STACKLIST_H_INCLUDED
