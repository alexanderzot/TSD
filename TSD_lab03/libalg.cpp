#include "libalg.h"

unsigned long long tick(void)
{
    unsigned long long d;
    __asm__ __volatile__ ("rdtsc" : "=A" (d) );
    return d;
}

void sort(student_t *st, int cnt)
{
    // alg
    for (int i = 0; i < cnt - 1; ++i)
    {
        student_t cur = st[i];
        int pos = i;
        for (int j = i + 1; j < cnt; ++j)
        {
            if (st[j].height < cur.height)
            {
                cur = st[j];
                pos = j;
            }
        }
        // swap
        student_t tmp = st[i];
        st[i] = st[pos];
        st[pos] = tmp;
    }
}

void sort_q(student_t *st, int cnt)
{
    long i = 0, j = cnt - 1;
    student_t temp, p;

    p = st[cnt >> 1];

    // процедура разделения
    do {
        while (st[i].height < p.height)
            i++;
        while (st[j].height > p.height)
            j--;

        if (i <= j)
        {
          temp = st[i];
          st[i] = st[j];
          st[j] = temp;
          i++;
          j--;
        }
    }
    while (i <= j);

    if (j > 0)
        sort_q(st, j);
    if (cnt > i)
        sort_q(st + i, cnt - i);
}

void sort2(key_sort_t *key_sort, int cnt)
{
    // sort key_sort
    for (int i = 0; i < cnt - 1; ++i)
    {
        key_sort_t cur = key_sort[i];
        int pos = i;
        for (int j = i + 1; j < cnt; ++j)
        {
            if (key_sort[j].height < cur.height)
            {
                cur = key_sort[j];
                pos = j;
            }
        }
        // swap
        key_sort_t tmp = key_sort[i];
        key_sort[i] = key_sort[pos];
        key_sort[pos] = tmp;
    }
}

void sort2_q(key_sort_t *st, int cnt)
{
    long i = 0, j = cnt - 1;
    key_sort_t temp, p;

    p = st[cnt >> 1];

    // процедура разделения
    do {
        while (st[i].height < p.height)
            i++;
        while (st[j].height > p.height)
            j--;

        if (i <= j)
        {
          temp = st[i];
          st[i] = st[j];
          st[j] = temp;
          i++;
          j--;
        }
    }
    while (i <= j);

    if (j > 0)
        sort2_q(st, j);
    if (cnt > i)
        sort2_q(st + i, cnt - i);
}
