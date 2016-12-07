#include "hash_close.h"

HashClose::HashClose(unsigned int str_count)
{
    this->size = get_next_simple(str_count);
    this->table = (char **)calloc(this->size, sizeof(char *));
    this->cnt = 0;
}

HashClose::~HashClose(void)
{
    for (register unsigned int i = 0; i < this->size; ++i)
    {
        free(this->table[i]);
    }
    free(this->table);
    this->size = 0;
}

unsigned int HashClose::get_hash(const char *str)
{
    unsigned int hash = 0;
    for(; *str; str++)
    {
        hash = (hash * 1664525) + (unsigned char)(*str) + 1013904223;
    }
    return hash;
}

int HashClose::insert(const char *str)
{
    unsigned int index = get_hash(str);
    unsigned int i = 0;
    index %= this->size;
    while(this->table[index])
    {
        index = (index + 1) % this->size;
        if (++i == this->size)
            return 0;
    }
    this->table[index] = (char *)str;
    this->cnt++;
    return 1;
}

char *HashClose::search(const char *str)
{
    this->cmp = 1;
    unsigned int index = get_hash(str);
    unsigned int i = 0;
    index %= this->size;
    if (!this->table[index])
        return NULL;
    while(strcmp(str, this->table[index]) != 0)
    {
        this->cmp++;
        index = (index + 1) % this->size;
        if (++i == this->size || !this->table[index])
            return NULL;
    }
    return this->table[index];
}

void HashClose::print(void)
{
    printf("\nSIZE: %d\n", this->size);
    for (register unsigned int i = 0; i < this->size; ++i)
    {
        printf("%d) %s\n", i + 1, this->table[i] == NULL ? "NULL" : this->table[i]);
    }
}

unsigned HashClose::get_memory(void)
{
    return this->size * sizeof(char *);
}

unsigned HashClose::get_cmp(void)
{
    return this->cmp;
}
