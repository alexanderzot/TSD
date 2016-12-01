#include "libdyn.h"


CDyn::CDyn(void)
{
    this->data = NULL;
    this->len = 0;
    this->allocated = 0;
    this->step = 2;
}

CDyn::~CDyn(void)
{
    for (register size_t i = 0; i < this->len; ++i)
    {
        free(this->data[i]);
        this->data[i] = NULL;
    }
    free(this->data);
    this->data = NULL;
}

int CDyn::insert(const char *value)
{
    if (!this->data)
    {
        this->data = (char **)malloc(INIT_SIZE * sizeof(char *));
        if (!this->data)
            return -1;
        this->allocated = INIT_SIZE;
    }
    else if (this->len >- this->allocated)
    {
        char **tmp = (char **)realloc(this->data,
                                  this->allocated * this->step * sizeof(char *));
        if (!tmp)
            return -1;
        this->data = tmp;
        this->allocated *= this->step;
    }
    this->data[this->len++] = (char *)value;
    return 0;
}

int CDyn::remove(int index)
{
    if (index < 0 || index >= this->len)
        return -1;
    memmove(this->data + index,
            this->data + index + 1,
            (this->len - index + 1) * sizeof(char *)
            );
    this->len--;
    return 0;
}

char *CDyn::get(int index)
{
    if (index < 0 || index >= this->len)
        return NULL;
    return this->data[index];
}

void  CDyn::print(void)
{
    if (!this->len)
        std::cout << "Dynamic array is empty!";
    for (register size_t i = 0; i < this->len; ++i)
    {
        std::cout << this->data[i] << " ";
    }
}

void CDyn::remove_char(char ch)
{
    for (int i = 0; i < this->len; ++i)
    {
        if (this->get(i)[0] == ch)
            this->remove(i);
    }
}
