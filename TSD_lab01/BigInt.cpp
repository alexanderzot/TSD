#include "BigInt.h"

BigInt::BigInt()
{
    for(int i = 0; i < MAX_SIZE; ++i)
        this->digit[i] = 0;
    this->count = 0;
    this->sign = 1;
}

const char BigInt::get_digit(const int i) const
{
    return this->digit[i];
}

const int BigInt::get_count(void) const
{
    return this->count;
}

const char BigInt::get_sign(void) const
{
    return this->sign;
}

void BigInt::digit_reverse(void)
{
    for (int i = 0; i < this->count / 2; ++i)
    {
        char n = this->digit[i];
        this->digit[i] = this->digit[this->count - i - 1];
        this->digit[this->count - i - 1] = n;
    }
}

const int BigInt::input(void)
{
    cout << "BigInt = ";
    BigInt();
    char ch;
    scanf("%c", &ch);
    if(ch == '\n')
    {
        cout << "Error of input!" << endl;
        return 1;
    }
    char *p = NULL;
    int state = 0;
    while(ch != '\n')
    {
        if(!isdigit(ch))
        {
            if ((ch == '+' or ch == '-') and p == NULL)
            {
                if (state == 0)
                {
                    state = 1;
                    this->sign = ch == '-' ? -1 : 1;
                }
                else
                {
                    cout << "Error of input!" << endl;
                    return 1;
                }
            }
            else if (!isspace(ch))
            {
                cout << "Error of input!" << endl;
                while(ch != '\n')
                    scanf("%c", &ch);
                return 1;
            }
        }
        else
        {
            if(p == NULL && ch == '0')
            {
                scanf("%c", &ch);
                continue;
            }
            if(p == NULL)
                p = this->digit;
            *p++ = ch - '0';
            this->count++;
        }
        scanf("%c", &ch);
    }
    if(this->count > MAX_INPUT_SIZE)
    {
        cout << "BigInt is to long!" << endl;
        return 1;
    }
    this->digit_reverse();
    return 0;
}
