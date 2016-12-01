#ifndef LIBDYN_H_INCLUDED
#define LIBDYN_H_INCLUDED

#include <iostream>
#include <stdlib.h>
#include <string.h>

#define INIT_SIZE 1

class CDyn
{
private:
    char **data;
    int len;
    int allocated;
    int step;
public:
    CDyn(void);
    ~CDyn(void);
    int insert(const char *num);
    int remove(int index);
    char *get(int index);
    void print(void);
    void remove_char(char ch);
};


#endif // LIBDYN_H_INCLUDED
