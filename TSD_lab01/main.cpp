#include "BigDouble.h"

int main(void)
{
    BigInt a;
    BigDouble b;
    if(!a.input() && !b.input())
    {
        if(b.is_zero())
        {
            cout << "Devision by zero!" << endl;
            return EXIT_FAILURE;
        }
        BigDouble res = a / b;
        if(res.is_zero())
            cout << "0" << endl;
        else if(!res.get_error())
            cout << res << endl;
        return EXIT_SUCCESS;
    }
    return EXIT_FAILURE;
}
