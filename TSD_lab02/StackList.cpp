#include "StackList.h"

int StackList::add_free(const node_t *adr)
{
    // first alloc
    if ( !this->free_mem )
    {
        this->free_size = FREE_BEGIN_SIZE;
        this->free_pos = 0;
        this->free_mem = (const node_t **)malloc( sizeof(const node_t *) * this->free_size );
    }
    // copy elements to new array if memory out
    if (this->free_pos >= this->free_size )
    {
        size_t tmp_size = this->free_size * 2;
        const node_t **tmp = (const node_t **)malloc( sizeof(const node_t *) * tmp_size );
        if (!tmp)
            return EXIT_FAILURE;
        for (int i = 0; i < this->free_pos; ++i)
            tmp[i] = this->free_mem[i];
        this->free_pos = this->free_size;
        this->free_size = tmp_size;
    }
    this->free_mem[ this->free_pos++ ] = adr;
    return EXIT_SUCCESS;
}

void StackList::del_free(const node_t *adr)
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

void StackList::print_free(void)
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

StackList::StackList(const size_t max_size)
{
    this->head = NULL;
    this->max_size = max_size;
    this->cur_size = 0;
    this->free_mem = NULL;
    this->free_size = 0;
    this->free_pos = 0;
    this->free_act = 1;
}

StackList::~StackList()
{
    // free memory of list
    while (this->head)
    {
        node_t *next = this->head->next;
        free(this->head);
        this->head = next;
    }
    // zero count
    this->max_size = 0;
    this->cur_size = 0;
    // free free memory
    if (this->free_mem)
        free(this->free_mem);
    this->free_mem = NULL;
    this->free_size = 0;
    this->free_pos = 0;
}

int StackList::push(const type_t value)
{
    // add element
    if (this->cur_size >= this->max_size)
        return SL_MAX_COUNT;
    this->cur_size++;

    node_t *node = (node_t *)malloc( sizeof(node_t) );
    if (!node)
        return SL_MEM_ERROR;
    this->del_free(node);
    node->value = value;
    node->next = this->head;
    this->head = node;
    return SL_SUCCESS;
}

int StackList::pop(type_t *value)
{
    if (!value)
        return SL_ERROR;
    if (!this->head)
        return SL_EMPTY;
    // sub element
    this->cur_size--;
    // save currenr element
    node_t *node = this->head;
    // go to next element
    this->head = this->head->next;
    // return value
    *value = node->value;
    // save address of free memory and free memory
    if (this->free_act && this->add_free(node))
    {
        free(node);
        return SL_ERROR;
    }
    free(node);
    return SL_SUCCESS;
}

node_t *StackList::get_head(void)
{
    return this->head;
}

void StackList::free_switch(void)
{
    if (this->free_act)
        this->free_act = 0;
    else
        this->free_act = 1;
}

void StackList::print(void)
{
    if (!this->head)
    {
        std::cout << "\nStack is empty!" << std::endl;
        return;
    }
    std::cout << "\nStack:" << std::endl;
    node_t *node = head;
    while (node)
    {
        std::cout << "  value: " << node->value << "  address: " << node << std::endl;
        node = node->next;
    }
}
