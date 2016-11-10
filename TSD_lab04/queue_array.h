#ifndef QUEUE_ARRAY_H_INCLUDED
#define QUEUE_ARRAY_H_INCLUDED

#include "types.h"

class Queue_array
{
private:
    request *arr;
    unsigned int max_size;
    unsigned int pos_begin;
    unsigned int pos_end;
    unsigned int cur_cnt;
    bool new_size(unsigned int size);
    bool is_full(void);
public:
    Queue_array();
    ~Queue_array();
    bool push_end(request element);
    request pop_front(void);
    void print(void);
    bool is_empty(void);
    unsigned int get_size(void);
    void free_print(void);
    bool insert_pos(request element, size_t pos);
};

#endif // QUEUE_ARRAY_H_INCLUDED
