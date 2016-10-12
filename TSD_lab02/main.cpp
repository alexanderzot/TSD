#include <iostream>
#include <stdio.h>
#include <ctime>
#include "DoubleStackArray.h"
#include "StackList.h"

#define ITERATIONS 100000

using namespace std;

unsigned short menu_size(void)
{
    long long int stack_size = 0;
    do
    {
        printf("\nStack size:\n");
        printf(" Max size is 4294967295 and larger zero\n");
        printf("Input stack size: ");
        scanf("%lld", &stack_size);
        // read all chars
        char ch;
        while( scanf("%c", &ch) && ch != '\n' )
            stack_size = 0;
    }
    while( stack_size <= 0 || stack_size > 4294967295 );
    return stack_size;
}

type_t menu_value(void)
{
    type_t value = 0;
    int flag = 0;
    do
    {
        flag = 0;
        printf("\nValue: ");
        flag = scanf(VALUE_MASK, &value);
        // read all chars
        char ch;
        while( scanf("%c", &ch) && ch != '\n' )
            flag = 0;
    }
    while( flag == 0 );
    return value;
}

void menu_stack_array(unsigned short n_size)
{
    DoubleStackArray ds(n_size);
    if (!ds.is_create())
    {
        printf("Double stack array error of allocate mamory!\n");
        ds.~DoubleStackArray();
        return;
    }
    int menu = 0;
    do
    {
        //print menu
        printf("\nChoose operation:\n");
        printf(" [1]: Push head\n");
        printf(" [2]: Pop head\n");
        printf(" [3]: Print head\n");
        printf(" [4]: Push tail\n");
        printf(" [5]: Pop tail\n");
        printf(" [6]: Print tail\n");
        printf(" [7]: Exit\n");
        // input
        printf("Input: ");
        scanf("%d", &menu);
        // error index
        if (menu > 7 || menu < 1)
            menu = 0;
        // read all chars
        char ch;
        while( scanf("%c", &ch) && ch != '\n' )
            menu = 0;
        if (menu == 1)
        {
            type_t value = menu_value();
            if (ds.push_head(value))
                printf("\nStack head is full!\n");
            else
                printf("\nValue is added!\n");
        }
        if (menu == 2)
        {
            type_t value = 0;
            if (ds.pop_head(&value))
                printf("\nStack head is empty!\n");
            else
                printf("\npop from head: "VALUE_MASK"\n", value);
        }
        if (menu == 3)
        {
            ds.print_head();
        }
        if (menu == 4)
        {
            type_t value = menu_value();
            if (ds.push_tail(value))
                printf("\nStack tail is full!\n");
            else
                printf("\nValue is added to stack tail!\n");
        }
        if (menu == 5)
        {
            type_t value = 0;
            if (ds.pop_tail(&value))
                printf("\nStack tail is empty!\n");
            else
                printf("\npop from tail: "VALUE_MASK"\n", value);
        }
        if (menu == 6)
            ds.print_tail();
    }
    while( menu != 7 );
    ds.~DoubleStackArray();
}

void menu_stack_list(unsigned short n_size)
{
    StackList ls(n_size);
    int menu = 0;
    do
    {
        //print menu
        printf("\nChoose operation:\n");
        printf(" [1]: Push\n");
        printf(" [2]: Pop\n");
        printf(" [3]: Print\n");
        printf(" [4]: Print adrress of free memory\n");
        printf(" [5]: Exit\n");
        // input
        printf("Input: ");
        scanf("%d", &menu);
        // error index
        if (menu > 5 || menu < 1)
            menu = 0;
        // read all chars
        char ch;
        while( scanf("%c", &ch) && ch != '\n' )
            menu = 0;
        if (menu == 1)
        {
            type_t value = menu_value();
            if (ls.push(value))
                printf("\nStack is full!\n");
            else
                printf("\nValue is added!\n");
        }
        if (menu == 2)
        {
            type_t value = 0;
            if (ls.pop(&value))
                printf("\nStack is empty!\n");
            else
                printf("\npop element: "VALUE_MASK"\n", value);
        }
        if (menu == 3)
            ls.print();
        if (menu == 4)
            ls.print_free();
    }
    while( menu != 5 );
    ls.~StackList();
}

int main()
{
    int menu1 = 0;
    do
    {
        //print menu
        printf("\nChoose type of stack:\n");
        printf(" [1]: Double stack array\n");
        printf(" [2]: Stack list\n");
        printf(" [3]: Double stack time\n");
        printf(" [4]: Stack list time\n");
        printf(" [5]: Exit\n");
        // input
        printf("Input: ");
        scanf("%d", &menu1);
        // error index
        if (menu1 > 5 || menu1 < 1)
            menu1 = 0;
        // read all chars
        char ch;
        while( scanf("%c", &ch) && ch != '\n' )
            menu1 = 0;
        // get size
        unsigned short s_size = 0;
        if (menu1 == 1)
        {
            s_size = menu_size();
            menu_stack_array(s_size);
        }
        if (menu1 == 2)
        {
            s_size = menu_size();
            menu_stack_list(s_size);
        }
        if (menu1 == 3)
        {
            s_size = menu_size();
            DoubleStackArray ds(s_size);
            clock_t begin_time = clock();
            for (int j = 0; j < ITERATIONS; ++j)
            {
                for (int i = 0; i < s_size; ++i)
                {
                    if (i % 2)
                        ds.push_head(i);
                    else
                        ds.push_tail(i);
                }
                for (int i = 0; i < s_size; ++i)
                {
                    type_t num = 0;
                    if (i % 2)
                        ds.pop_head(&num);
                    else
                        ds.pop_tail(&num);
                }
            }
            cout << "\nTime double stack-array: " << clock() - begin_time << " msec";
            cout << ", iterations: " << ITERATIONS << endl;
        }
        if (menu1 == 4)
        {
            s_size = menu_size();
            StackList ls(s_size);
            ls.free_switch();
            clock_t begin_time = clock();
            for (int j = 0; j < ITERATIONS; ++j)
            {
                for (int i = 0; i < s_size; ++i)
                    ls.push(i);
                for (int i = 0; i < s_size; ++i)
                {
                    type_t num = 0;
                    ls.pop(&num);
                }
            }
            cout << "\nTime stack-list: " << clock() - begin_time << " msec";
            cout << ", iterations: " << ITERATIONS << endl;
        }
    }
    while( menu1 != 5 );
    return EXIT_SUCCESS;
}
