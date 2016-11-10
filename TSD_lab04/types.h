#ifndef TYPES_H_INCLUDED
#define TYPES_H_INCLUDED

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>
#include <math.h>

#define BEGIN_CNT 5000;

typedef struct
{
    unsigned int type;
} request;

struct request_list
{
    request value;
    struct request_list *next;
};

typedef struct
{
    double model_time;
    double obrab_time;
    double stay_time;
    unsigned type_in1;
    unsigned type_in2;
    unsigned type_out1;
    unsigned type_out2;
    int error_flag;
} request_info;

typedef struct
{
    unsigned from;
    unsigned to;
} time_interval;

#endif // TYPES_H_INCLUDED
