#ifndef HASH_OPEN_H_INCLUDED
#define HASH_OPEN_H_INCLUDED

#include "libio.h"
#include "string.h"

typedef struct hash_node
{
    char *value;
    struct hash_node *next;
} hash_node;

class HashOpen
{
private:
    hash_node **table;
    unsigned int cnt;
    unsigned int get_hash(const char *str);
    unsigned cmp;
public:
    unsigned size;
    HashOpen(unsigned int str_count);
    ~HashOpen(void);
    int insert(const char *str);
    char *search(const char *str);
    void print(void);
    unsigned get_memory(void);
    unsigned get_cmp(void);
};
#endif // HASH_OPEN_H_INCLUDED
