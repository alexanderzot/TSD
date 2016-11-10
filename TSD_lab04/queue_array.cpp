#include "queue_array.h"

Queue_array::Queue_array()
{
    this->max_size = BEGIN_CNT;
    this->pos_begin = 0;
    this->pos_end = 0;
    this->cur_cnt = 0;
    this->arr = (request *)malloc( sizeof(request) * this->max_size );
}

Queue_array::~Queue_array()
{
    this->max_size = 0;
    this->pos_begin = 0;
    this->pos_end = 0;
    this->cur_cnt = 0;
    if(arr)
        free(this->arr);
    this->arr = NULL;
}

bool Queue_array::push_end(request elem)
{
    if (this->is_full())
        if (!this->new_size( this->max_size << 1 ))
        {
            return false;
        }

    this->arr[this->pos_end] = elem;
    this->pos_end = (this->pos_end + this->max_size + 1) % this->max_size;
    this->cur_cnt++;
    return true;
}

request Queue_array::pop_front(void)
{
    request tmp = this->arr[this->pos_begin];
    this->pos_begin = (this->pos_begin + this->max_size + 1) % this->max_size;
    this->cur_cnt--;
    return tmp;
}

bool Queue_array::is_full(void)
{
    return this->cur_cnt == this->max_size;
}

bool Queue_array::new_size(unsigned int size)
{
    assert(size >= this->max_size);
    request *tmp = (request *)malloc( sizeof(request) * size );
    if (tmp == NULL)
        return false;
    unsigned int j = 0;
    unsigned int i = this->pos_begin;
    for (unsigned int j = 0; j < this->cur_cnt; ++j)
    {
        tmp[j] = this->arr[i];
        i = (i + 1 + this->max_size) % this->max_size;
    }
    this->pos_begin = 0;
    this->pos_end = cur_cnt;
    free(this->arr);
    this->arr = tmp;
    this->max_size = size;
    return true;
}

void Queue_array::print(void)
{
    if (this->is_empty())
    {
        std::cout << "is empty!" << std::endl;
        return;
    }
    unsigned int i = this->pos_begin;
    for (unsigned int j = 0; j < this->cur_cnt; ++j)
    {
        std::cout << this->arr[i].type << " ";
        i = (i + 1 + this->max_size) % this->max_size;
    }
    std::cout << std::endl;
}

bool Queue_array::is_empty(void)
{
    return !this->cur_cnt;
}

void Queue_array::free_print(void)
{
    std::cout << "";
}

unsigned int Queue_array::get_size(void)
{
    return this->cur_cnt;
}

bool Queue_array::insert_pos(request element, size_t pos)
{
    bool res = false;
    if (this->cur_cnt <= pos)
        res = this->push_end(element);
    else
    {
        request t = {1};
        res = this->push_end(t);
        this->arr[(this->pos_begin + pos + this->max_size - 1) % this->max_size] = element;
    }
    return res;
}
