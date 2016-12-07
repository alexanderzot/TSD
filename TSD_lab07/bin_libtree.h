#ifndef BIN_LIBTREE_H_INCLUDED
#define BIN_LIBTREE_H_INCLUDED

#include <string>
#include <strings.h>
#include "string.h"
#include <iostream>
#include "stdlib.h"

#define ROT_RIGHT 2
#define ROT_LEFT -2

#define LU_BORDER (char)218
#define LD_BORDER (char)192
#define HOR_BORDER (char)196
#define VER_BORDER (char)179

struct node_bin
{
    const char *value;
    node_bin *left;
    node_bin *right;
    unsigned int count;
};

class CTreeBin
{
private:
    node_bin *head;
    unsigned cnt;
    void free_tree(node_bin *p);
    void insert_tree(node_bin *p, const char *value);
    node_bin *search_tree(node_bin *p, const char *value);
    unsigned cmp;
    void print_tree(node_bin *p, int num);
public:
    CTreeBin(void);
    ~CTreeBin(void);
    void insert(const char *value);
    node_bin *search(const char *value);
    int is_empty(void);
    unsigned get_memory(void);
    unsigned get_cmp(void);
    void print(void);
};

#endif // BIN_LIBTREE_H_INCLUDED
