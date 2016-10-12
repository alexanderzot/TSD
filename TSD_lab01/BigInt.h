#ifndef BIG_INT_H
#define BIG_INT_H

#define MAX_INPUT_SIZE 30

#include <iostream>
#include <stdio.h>

using namespace std;

#define MAX_SIZE MAX_INPUT_SIZE * 4

class BigInt
{
private:
    int count;
    char digit[MAX_SIZE];
    char sign;
    void digit_reverse(void);
public:
    BigInt();
    const char get_digit(const int i) const;
    const int get_count(void) const;
    const char get_sign(void) const;
    const int input(void);
};

#endif
