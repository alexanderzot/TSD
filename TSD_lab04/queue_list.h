#ifndef QUEUE_LIST_H_INCLUDED
#define QUEUE_LIST_H_INCLUDED

#include "types.h"

class Queue_list
{
private:
    struct request_list
    {
        request value;
        struct request_list *next;
    };
    request_list *head;
    request_list *tail;
    unsigned int cur_cnt;
    // array free memory of node_t *
    const request_list **free_mem;
    size_t free_size;
    size_t free_pos;
    int add_free(const request_list *adr);
    void del_free(const request_list *adr);
public:
    Queue_list();
    ~Queue_list();
    bool push_end(request element);
    request pop_front(void);
    bool is_full(void);
    void print(void);
    bool is_empty(void);
    unsigned int get_size(void);
    void free_print(void);
    bool insert_pos(request element, size_t pos);
};

#endif // QUEUE_LIST_H_INCLUDED
