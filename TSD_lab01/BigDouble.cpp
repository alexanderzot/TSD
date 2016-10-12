#include "BigDouble.h"

void BigDouble::digit_reverse(void)
{
    for (int i = 0; i < this->count / 2; ++i)
    {
        char n = this->digit[i];
        this->digit[i] = this->digit[this->count - i - 1];
        this->digit[this->count - i - 1] = n;
    }
}

void BigDouble::fill_zero(void)
{
    for(int i = 0; i < DEVIDENT; i++)
    {
        this->digit[i + DEVIDENT] = this->digit[i];
    }
    for(int i = 0; i < DEVIDENT; i++)
    {
        this->digit[i] = 0;
    }
    this->count += DEVIDENT;
    this->exp -= DEVIDENT;
}

void BigDouble::mul_dec(void)
{
    for (int i = this->count; i >= 1; i--)
        this->digit[i] = this->digit[i-1];
    this->digit[0] = 0;
    if (this->digit[this->count])
        this->count++;
}

const int BigDouble::is_zero(void) const
{
    for(int i = 0; i < this->count; i++)
    {
        if(this->digit[i])
            return 0;
    }
    return 1;
}

const int BigDouble::get_error(void) const
{
    return this->error;
}

BigDouble::BigDouble()
{
    for(int i = 0; i < MAX_SIZE; ++i)
        this->digit[i] = 0;
    this->count = 0;
    this->exp = 0;
    this->sign = 1;
    this->error = 0;
}

BigDouble::BigDouble(const BigInt obj)
{
    for(int i = 0; i < MAX_SIZE; ++i)
        this->digit[i] = obj.get_digit(i);
    this->count = obj.get_count();
    this->exp = 0;
    this->sign = obj.get_sign();
}

ostream& operator <<(ostream &stream, const BigDouble &obj)
{
    // print only znach digit
    int num = 0;
    for (int i = 0; i < obj.count; ++i)
    {
        if (obj.digit[i])
            break;
        num += 1;
    }
    // print
    stream << ((obj.sign == -1) ? "-0." : "+0.");
    for(int i = obj.count - 1; i >= num && i >= (obj.count - MAX_INPUT_SIZE - 1); i--)
        stream << obj.digit[i];
    stream << "e" << obj.exp << endl;
    return stream;
}
void BigDouble::normal(void)
{
    int i = 0;
    while(this->count > 0 && this->digit[this->count - 1] == 0)
        this->count--;
    this->exp += this->count;
    while(this->digit[i] == 0 && i < this->count)
        i++;
    for(int j = i; j < this->count; j++)
    {
        this->digit[j - i] = this->digit[j];
    }
    this->count -= i;
    if(this->count <= 0)
        this->count = 1;
    this->digit_reverse();
    // norm exp
    if(exp < 0 && fabs(this->exp) > EXP_LIMIT)
    {
        int sdwig = EXP_LIMIT - this->exp;
        if(sdwig <= 30)
        {
            for (i = 0; i < this->count; i++)
            {
                this->digit[i + sdwig] = this->digit[i];
            }
            for(i = 0; i < sdwig; ++i)
            {
                this->digit[i] = 0;
            }
        }
        else
        {
            for(i = 0; i < MAX_INPUT_SIZE; i++)
                this->digit[i] = 0;
        }
        this->exp = -EXP_LIMIT;
        count = MAX_INPUT_SIZE;
    }
    while(true)
    {
        if (this->exp > 0 && exp > EXP_LIMIT)
        {
            cout << "Out of range" << endl;
            error = 1;
            return;
        }
        int digit_help[MAX_SIZE];
        for (i = 0; i <= MAX_INPUT_SIZE + 1; i++)
            digit_help[i] = this->digit[i];
        i = MAX_INPUT_SIZE - 1;
        digit_help[i] += digit_help[MAX_INPUT_SIZE] >= 5 ? 1 : 0;
        while (i > 0 && digit_help[i] > 9)
        {
            digit_help[i--] %= 10;
            digit_help[i] += 1;
        }
        if (i == 0 && digit_help[i] > 9)
        {
            this->mul_dec();
            this->exp += 1;
        }
        else
        {
            if (exp > 0 && this->exp > EXP_LIMIT)
            {
                cout << "Range exp is out!" << endl;
                error = 1;
                return;
            }
            for (i = 0; i < MAX_INPUT_SIZE; i++)
            {
                this->digit[i] = digit_help[i];
            }
            count = MAX_INPUT_SIZE;
            break;
        }
    }
    this->digit_reverse();
}

const int BigDouble::input(void)
{
    cout << "BigFloat = ";
    BigDouble();
    int *adr = NULL, *point = NULL;
    char ch;
    scanf("%c", &ch);
    if(ch == '\n')
    {
        cout << "Error of input" << endl;
        return 1;
    }
    int state = 0;
    while( tolower(ch) != 'e' && ch != '\n')
    {
        // input not a digit
        if(!isdigit(ch))
        {
            if ((ch == '+' or ch == '-') and adr == NULL)
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
            else if (ch == '.' and point == NULL)
                point = adr == NULL ? this->digit : adr;
            else if (!isspace(ch))
            {
                cout << "Error of input" << endl;
                while(ch != '\n')
                    scanf("%c", &ch);
                this->error = 1;
                return 1;
            }
        }
        // signum
        else
        {
            if(adr == NULL && ch == '0')
            {
                scanf("%c", &ch);
                continue;
            }
            if(adr == NULL)
                adr = this->digit;
            *adr = ch - '0';
            adr++;
            this->count++;
        }
        scanf("%c", &ch);
    }
    // exp
    if (tolower(ch) == 'e' and scanf("%d", &this->exp) != 1)
    {
        cout << "Error in input" << endl;
        while(ch != '\n')
            scanf("%c", &ch);
        this->error = 1;
        return 1;
    }
    // value exp
    if((adr - this->digit > MAX_INPUT_SIZE) or (fabs(this->exp) > EXP_LIMIT))
    {
        cout << "Error in input" << endl;
        this->error = 1;
        return 1;
    }
    if(point == NULL)
        point = adr;
    // calc exp
    this->exp -= (adr - point);
    this->digit_reverse();
    return 0;
}

bool operator <(const BigDouble & left, const BigDouble & right)
{
    if (left.count != right.count)
        return left.count < right.count;
    for (int i = left.count - 1; i >= 0; i--)
    {
        if (left.digit[i] != right.digit[i])
            return left.digit[i] < right.digit[i];
    }
    return false;
}

bool operator ==(const BigDouble & left, const BigDouble & right)
{
    if (left.count != right.count)
        return false;
    for (int i = left.count - 1; i >= 0; i--)
    {
        if (left.digit[i] != right.digit[i])
            return false;
    }
    return true;
}

bool operator !=(const BigDouble & left, const BigDouble & right)
{
    return !(left == right);
}

bool operator >=(const BigDouble & left, const BigDouble & right)
{
    return left > right || left == right;
}

bool operator <=(const BigDouble & left, const BigDouble & right)
{
    return left < right || left == right;
}

bool operator >(const BigDouble & left, const BigDouble & right)
{
    return !(left <= right);
}

BigDouble operator *(const BigDouble & left, const int right)
{
    BigDouble res;
    res.count = left.count;
    int r = 0;
    for (int i = 0; i < res.count | r; i++)
    {
        res.digit[i] = left.digit[i] * right + r;
        r = res.digit[i] / 10;
        res.digit[i] -= r * 10;
    }
    while (res.digit[res.count])
        res.count++;
    return res;
}

BigDouble operator *(const int left, const BigDouble & right)
{
    return right * left;
}

BigDouble operator -(const BigDouble & left, const BigDouble & right)
{
    BigDouble res = left;
    int r = 0;
    for (int i = 0; i < res.count; i++)
    {
        res.digit[i] -= right.digit[i];
        if (res.digit[i] < 0)
        {
            res.digit[i] += 10;
            res.digit[i + 1]--;
        }
    }
    int pos = res.count-1;
    while (pos && !res.digit[pos])
        pos--;
    res.count = pos + 1;
    return res;
}

BigDouble operator /(const BigInt & left, const BigDouble & right)
{
    BigDouble res;
    BigDouble tmp;
    BigDouble a_copy = BigDouble(left);
    a_copy.fill_zero();
    tmp.count = 1;
    for (int i = a_copy.count - 1; i >= 0; i--)
    {
        tmp.mul_dec();
        tmp.digit[0] = a_copy.digit[i];
        int x = 0;
        for (int i = 9; i >=0; --i)
        {
            BigDouble cur = right * i;
            if (cur <= tmp)
            {
                x = i;
                break;
            }
        }
        res.digit[i] = x;
        BigDouble mul = right * x;
        tmp = tmp - mul;
    }
    res.count = a_copy.count;
    int pos = a_copy.count;
    while (pos >= 0 && !res.digit[pos])
        pos--;
    res.count = pos + 1;
    res.exp = a_copy.exp - right.exp;
    res.sign = left.get_sign() * right.sign;
    res.normal();
    return res;
}
