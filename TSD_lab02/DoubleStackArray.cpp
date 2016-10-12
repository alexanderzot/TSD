#include "DoubleStackArray.h"

DoubleStackArray::DoubleStackArray(const size_t max_size)
{
    this->max_size = max_size;
    // create array
    if (this->max_size == 0)
        this->data = NULL;
    else
        this->data = (type_t *)malloc( sizeof(type_t) * this->max_size );
    // calculate address head and tail
    if (this->data)
    {
        this->head = this->data - 1;
        this->tail = this->data + this->max_size;
    }
    else
    {
        this->head = NULL;
        this->tail = NULL;
    }
}

DoubleStackArray::~DoubleStackArray()
{
    // free array memory
    if (this->data)
        free( this->data );
    this->max_size = 0;
    this->head = NULL;
    this->tail = NULL;
}

int DoubleStackArray::is_create(void)
{
    return this->data != NULL;
}

int DoubleStackArray::push_head(const type_t value)
{
    if (this->data && this->head >= this->tail - 1 )
        return DSA_FAILURE;
    *(++this->head) = value;
    return DSA_SUCCESS;
}

int DoubleStackArray::push_tail(const type_t value)
{
    if (this->data && this->tail <= this->head + 1 )
        return DSA_FAILURE;
    *(--this->tail) = value;
    return DSA_SUCCESS;
}

int DoubleStackArray::pop_head(type_t *value)
{
    if (this->data && this->head < this->data && value)
        return DSA_FAILURE;
    *value = *(this->head--);
    return DSA_SUCCESS;
}

int DoubleStackArray::pop_tail(type_t *value)
{
    if (this->data && this->tail >= this->data + this->max_size && value)
        return DSA_FAILURE;
    *value = *(this->tail++);
    return DSA_SUCCESS;
}

void DoubleStackArray::print_head(void)
{
    if (this->data > this->head )
    {
        std::cout << "\nStack-head is empty!" << std::endl;
        return;
    }
    std::cout << "\nStack-head:" << std::endl;
    for (int i = this->head - this->data; i >= 0; --i)
    {
        std::cout << "  value: " << this->data[i] << std::endl;
        //std::cout << "  value: " << this->data[i] << "  address: " << this->data + i << std::endl;
    }
}

void DoubleStackArray::print_tail(void)
{
    if (this->data + this->max_size <= this->tail )
    {
        std::cout << "\nStack-tail is empty!" << std::endl;
        return;
    }
    std::cout << "\nStack-tail:" << std::endl;
    for (int i = this->tail - this->data; i < this->max_size; ++i)
    {
        std::cout << "  value: " << this->data[i] << std::endl;
        //std::cout << "  value: " << this->data[i] << "  address: " << this->data + i<< std::endl;
    }
}
