#ifndef LIBALG_H_INCLUDED
#define LIBALG_H_INCLUDED

#include "libio.h"
#include <stdlib.h>

unsigned long long tick(void);

typedef struct
{
    unsigned int index;
    byte_t height;
} key_sort_t;

void sort(student_t *st, int cnt);
void sort2(key_sort_t *st, int cnt);

void sort_q(student_t *st, int cnt);
void sort2_q(key_sort_t *st, int cnt);

#endif // LIBALG_H_INCLUDED
