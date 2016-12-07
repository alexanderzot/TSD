#ifndef HASH_CLOSE_H_INCLUDED
#define HASH_CLOSE_H_INCLUDED

#include "libio.h"
#include "string.h"

class HashClose
{
private:
    char **table;
    unsigned int cnt;
    unsigned int get_hash(const char *str);
    unsigned cmp;
public:
    unsigned size;
    HashClose(unsigned int str_count);
    ~HashClose(void);
    int insert(const char *str);
    char *search(const char *str);
    void print(void);
    unsigned get_memory(void);
    unsigned get_cmp(void);
};

#endif // HASH_CLOSE_H_INCLUDED
