#ifndef LIBIO_H_INCLUDED
#define LIBIO_H_INCLUDED

#include <stdio.h>
#include <iostream>
#include "libio.h"
#include <stdlib.h>
#include <string.h>

#define BEGIN_BUFF_SIZE 2
#define BUFF_SIZE 15 // need bigger 1

#define ERROR_NO 0
#define ERROR_EOF 2
#define ERROR_ALLOC_MEM 1

using namespace std;

char *read_line(FILE *f, int *err_code);
int menu_value(void);
int is_simple(unsigned num);
unsigned get_pred_simple(unsigned num);
unsigned get_next_simple(unsigned num);

#endif // LIBIO_H_INCLUDED
