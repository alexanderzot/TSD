#ifndef LIBTREE_H_INCLUDED
#define LIBTREE_H_INCLUDED


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

// not used yet
/*
#define RD_BORDER 217
#define RU_BORDER 191
#define CC_BORDER 197
#define CD_BORDER 193
#define RC_BORDER 180
#define LC_BORDER 195
#define CU_BORDER 194
*/

struct node
{
    const char *value;
    node *left;
    node *right;
    unsigned char height;
    unsigned int count;
    node (const char *value)
    {
        this->value = value;
        this->left = NULL;
        this->right = NULL;
        this->height = 1;
        this->count = 1;
    }
};

class CTree
{
private:
    node *head;
    unsigned char get_height(node *p);
    int calc_factor(node *p);
    void calc_height(node *p);
    node *left_rot(node *head);
    node *right_rot(node *head);
    node *balance(node *p);
    node *find_min(node *p);
    node *remove_min(node *p);
    node *remove_tree(node *p, const char *value, int *status);
    void remove_tree_char(node *p, char ch);
    node *insert_tree(node *p, const char *value);
    node *search_tree(node *p, const char *value);
    void print_tree(node *p, int num);
    void free_tree(node *p);
public:
    CTree(void);
    ~CTree(void);
    void insert(const char *value);
    int remove(const char *value);
    node *search(const char *value);
    int is_empty(void);
    void print(void);
    void remove_char(char ch);
};

#endif // LIBTREE_H_INCLUDED
