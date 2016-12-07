#include "hash_open.h"

HashOpen::HashOpen(unsigned int str_count)
{
    this->size = get_pred_simple(str_count);
    this->table = (hash_node **)calloc(this->size, sizeof(hash_node *));
    this->cnt = 0;
    for (register unsigned int i = 0; i < this->size; ++i)
    {
        this->table[i] = NULL;
    }
}

//add clear str
HashOpen::~HashOpen(void)
{
    for (register unsigned int i = 0; i < this->size; ++i)
    {
        hash_node *p = this->table[i];
        while (p)
        {
            free(p->value);
            p = p->next;
        }
        free(this->table[i]);
    }
    free(this->table);
    this->size = 0;
}

unsigned int HashOpen::get_hash(const char *str)
{
    unsigned int hash = 0;
    for(; *str; str++)
    {
        hash = (hash * 1664525) + (unsigned char)(*str) + 1013904223;
    }
    return hash;
}

int HashOpen::insert(const char *str)
{
    unsigned int index = get_hash(str);
    index %= this->size;
    hash_node *tmp = (hash_node *)calloc(1, sizeof(hash_node));
    if (!tmp)
        return 0;
    tmp->next = NULL;
    tmp->value = (char *)str;

    if (this->table[index] == NULL)
    {
        this->table[index] = tmp;
    }
    else
    {
        hash_node *p = this->table[index];
        while(p->next)
        {
            p = p->next;
        }
        p->next = tmp;
    }
    this->cnt++;
    return 1;
}

char *HashOpen::search(const char *str)
{
    this->cmp = 1;
    unsigned int index = get_hash(str);
    index %= this->size;

    if (this->table[index] == NULL)
    {
        return NULL;
    }
    else
    {
        hash_node *p = this->table[index];
        while(p)
        {
            this->cmp++;
            if (strcmp(str, p->value) == 0)
                return p->value;
            p = p->next;
        }
    }
    return NULL;
}

void HashOpen::print(void)
{
    printf("\nSIZE: %d\n", this->size);
    for (register unsigned int i = 0; i < this->size; ++i)
    {
        hash_node *p = this->table[i];
        printf("%d) ", i + 1);
        if (!p)
            printf("NULL");
        while (p)
        {
            printf("%s  ", p->value);
            p = p->next;
        }
        printf("\n");
    }
}

unsigned HashOpen::get_memory(void)
{
    return sizeof(this->table) + this->cnt * sizeof(hash_node);
}

unsigned HashOpen::get_cmp(void)
{
    return this->cmp;
}
