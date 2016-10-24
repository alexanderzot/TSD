#ifndef LIBIO_H_INCLUDED
#define LIBIO_H_INCLUDED

#include "types.h"
#include <stdio.h>
#include <string>

void input_name(student_t *st, FILE *f);
void input_sex(student_t *st, FILE *f);
void input_height(student_t *st, FILE *f);
void input_point(student_t *st, FILE *f);
void input_type(student_t *st, FILE *f);
void input_street(student_t *st, FILE *f);
void input_house_num(student_t *st, FILE *f);
void input_apart_num(student_t *st, FILE *f);
void input_hostel_num(student_t *st, FILE *f);
void input_room_num(student_t *st, FILE *f);
void input_student(student_t *st, FILE *f);

void print_student(student_t *st);

#endif // LIBIO_H_INCLUDED
