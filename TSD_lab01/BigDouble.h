#ifndef BIG_DOUBLE_H
#define BIG_DOUBLE_H

#include "BigInt.h"
#include "math.h"

#define EXIT_SUCCESS 0
#define EXIT_FAILURE 1
#define DEVIDENT MAX_SIZE - MAX_INPUT_SIZE
#define EXP_LIMIT 99999

using namespace std;

class BigDouble
{
private:
    int count;
    int digit[MAX_SIZE];
    int exp;
    char sign;
    char error;
    void digit_reverse(void);
    void mul_dec(void);
    void fill_zero(void);
    void normal(void);
public:
    BigDouble();
    BigDouble(const BigInt obj);

    const int input(void);
    const int get_error(void) const;
    const int is_zero(void) const;

    friend ostream& operator <<(ostream &stream, const BigDouble &obj);
    friend bool operator <(const BigDouble &left, const BigDouble &right);
    friend bool operator >(const BigDouble &left, const BigDouble &right);
    friend bool operator <=(const BigDouble &left, const BigDouble &right);
    friend bool operator >=(const BigDouble &left, const BigDouble &right);
    friend bool operator ==(const BigDouble &left, const BigDouble &right);
    friend bool operator !=(const BigDouble &left, const BigDouble &right);
    friend BigDouble operator -(const BigDouble &left, const BigDouble &right);
    friend BigDouble operator *(const BigDouble &left, const int right);
    friend BigDouble operator *(const int left, const BigDouble &right);
    friend BigDouble operator /(const BigInt &left, const BigDouble &right);
};

#endif
