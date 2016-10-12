#ifndef DOUBLESTACKARRAY_H_INCLUDED
#define DOUBLESTACKARRAY_H_INCLUDED

#include <iostream>
#include <stdlib.h>

typedef float type_t;
#define DSA_FAILURE 1
#define DSA_SUCCESS 0

#define VALUE_MASK "%f"

class DoubleStackArray
{
private:
    size_t max_size;
    type_t *data;
    type_t *head;
    type_t *tail;
public:
    DoubleStackArray(const size_t max_size = 10);
    ~DoubleStackArray();
    int is_create(void);
    int push_head(const type_t value);
    int push_tail(const type_t value);
    int pop_head(type_t *value);
    int pop_tail(type_t *value);
    void print_head(void);
    void print_tail(void);
};

#endif // DOUBLESTACKARRAY_H_INCLUDED
