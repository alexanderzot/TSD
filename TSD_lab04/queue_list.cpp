#include "queue_list.h"

Queue_list::Queue_list()
{
    this->head = NULL;
    this->tail = NULL;
    this->cur_cnt = 0;
    this->free_mem = NULL;
    this->free_size = 0;
    this->free_pos = 0;
}

Queue_list::~Queue_list()
{
    while (head != NULL)
    {
        struct request_list *tmp = this->head->next;
        free(head);
        this->head = tmp;
    }
    this->head = NULL;
    this->tail = NULL;
    this->cur_cnt = 0;
}

bool Queue_list::push_end(request element)
{
    struct request_list *tmp = (struct request_list *)malloc( sizeof(struct request_list) );
    if (!tmp)
        return false;
    tmp->value = element;
    tmp->next = NULL;
    if (this->head == NULL)
    {
        this->head = tmp;
    }
    if(this->tail)
    {
        this->tail->next = tmp;
    }
    this->tail = tmp;
    this->cur_cnt++;
    this->del_free(tmp);
    return true;
}

request Queue_list::pop_front(void)
{
    struct request_list *tmp = head;
    request res = head->value;
    this->head = this->head->next;
    if (this->head == NULL)
    {
        this->tail = NULL;
    }
    this->add_free(tmp);
    free(tmp);
    this->cur_cnt--;
    return res;
}

void Queue_list::print(void)
{
    if (this->is_empty())
    {
        std::cout << "is empty!" << std::endl;
        return;
    }
    struct request_list *tmp = this->head;
    while (tmp != NULL)
    {
        std::cout << tmp->value.type << " ";
        tmp = tmp->next;
    }
    std::cout << std::endl;
}

bool Queue_list::is_empty(void)
{
    return this->head == NULL;
}

unsigned int Queue_list::get_size(void)
{
    return this->cur_cnt;
}

// free memory
int Queue_list::add_free(const request_list *adr)
{
    // first alloc
    if ( !this->free_mem )
    {
        this->free_size = BEGIN_CNT;
        this->free_pos = 0;
        this->free_mem = (const request_list **)malloc( sizeof(const request_list *) * this->free_size );
    }
    // copy elements to new array if memory out
    if (this->free_pos >= this->free_size )
    {
        size_t tmp_size = this->free_size * 2;
        const request_list **tmp = (const request_list **)malloc( sizeof(const request_list *) * tmp_size );
        if (!tmp)
            return EXIT_FAILURE;
        for (int i = 0; i < this->free_pos; ++i)
            tmp[i] = this->free_mem[i];
        this->free_pos = this->free_size;
        this->free_size = tmp_size;
    }
    this->free_pos++;
    this->free_pos %= BEGIN_CNT;
    this->free_mem[this->free_pos] = adr;
    return EXIT_SUCCESS;
}

void Queue_list::del_free(const request_list *adr)
{
    int pos = -1;
    for (int i = 0; i < this->free_pos; ++i)
    {
        if (this->free_mem[i] == adr)
        {
            pos = i;
            break;
        }
    }
    if (pos == -1)
        return;
    for (int i = pos; i < this->free_pos - 1; ++i)
    {
        this->free_mem[i] = this->free_mem[i + 1];
    }
    this->free_pos--;
}

void Queue_list::free_print(void)
{
    if (this->free_pos == 0)
    {
        std::cout << "\nArea of free memory is empty!" << std::endl;
        return;
    }
    std::cout << "\nMemory of free:" << std::endl;
    for(int i = 0; i < this->free_pos; i++)
        std::cout << " [" << i + 1 << "] adress: " << this->free_mem[i] << std::endl;
    std::cout << std::endl;
}

bool Queue_list::insert_pos(request element, size_t pos)
{
    bool res = false;
    if (this->cur_cnt <= pos)
        res = this->push_end(element);
    else
    {
        request t = {1};
        res = this->push_end(t);
        struct request_list *node = this->head;
        del_free(node);
        for (size_t i = 0; i < pos - 1; ++i)
            node = node->next;
        node->value.type = 2;
    }
    return res;
}
