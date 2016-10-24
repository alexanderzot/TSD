#include <iostream>
#include <stdlib.h>
#include "libio.h"
#include "libalg.h"

#define BEGIN_CNT 2
#define ITERATION 100000

using namespace std;

int menu_value(void)
{
    int value = 0;
    int flag = 0;
    do
    {
        flag = 0;
        printf("\nValue: ");
        flag = scanf("%2d", &value);
        // read all chars
        char ch;
        while( scanf("%c", &ch) && ch != '\n' )
            flag = 0;
    }
    while( flag == 0 );
    return value;
}

int main()
{
    int max_cnt = BEGIN_CNT;
    int cur_cnt = 0;
    student_t *students = (student_t *)malloc( sizeof(student_t) * max_cnt );
    int menu1 = 0;
    do
    {
        //print menu
        printf("\n>Main menu:\n");
        printf(" [1]: Add student\n");
        printf(" [2]: Delete student\n");
        printf(" [3]: Sort student\n");
        printf(" [4]: Sort student with table key\n");
        printf(" [5]: Print student\n");
        printf(" [6]: Print student hostel\n");
        printf(" [7]: Read from file\n");
        printf(" [8]: Exit\n");
        // input
        printf("Input: ");
        scanf("%d", &menu1);
        // error index
        if (menu1 > 8|| menu1 < 1)
            menu1 = 0;
        // read all chars
        char ch;
        while( scanf("%c", &ch) && ch != '\n' )
            menu1 = 0;
        // add
        if (menu1 == 1)
        {
            if (cur_cnt >= max_cnt)
            {
                max_cnt <<= 1;
                student_t *tmp = (student_t *)malloc( sizeof(student_t) * max_cnt );
                if (!tmp)
                {
                    return 1;
                }
                for (int i = 0; i < cur_cnt; ++i)
                {
                    tmp[i] = students[i];
                }
                free(students);
                students = tmp;
            }
            input_student(&students[cur_cnt++], stdin);
        }
        // del
        if (menu1 == 2)
        {
            int num = 0;
            do
                num = menu_value();
            while( num <= 0 || num > cur_cnt);
            for (int i = num - 1; i < cur_cnt - 1; ++i)
            {
                students[i] = students[i + 1];
            }
            cur_cnt--;
        }
        // sort
        if (menu1 == 3)
        {
            // Sort
            unsigned long long time = 0;
            for (int i = 0; i < ITERATION; ++i)
            {
                student_t *st = (student_t *)malloc( sizeof(student_t) * cur_cnt );
                for (int i = 0; i < cur_cnt; ++i)
                {
                    st[i] = students[i];
                }
                unsigned long long tmp_time = tick();
                sort(st, cur_cnt);
                time += tick() - tmp_time;
                free(st);
            }
            printf("\nSort\n");
            printf("Time: %lld ticks\n", time);
            printf("Iterations: %d\n", ITERATION);
            printf("Avarage time: %lld ticks\n", time / ITERATION);
            // QSort
            time = 0;
            for (int i = 0; i < ITERATION; ++i)
            {
                student_t *st = (student_t *)malloc( sizeof(student_t) * cur_cnt );
                for (int i = 0; i < cur_cnt; ++i)
                {
                    st[i] = students[i];
                }
                unsigned long long tmp_time = tick();
                sort_q(st, cur_cnt);
                time += tick() - tmp_time;
                free(st);
            }
            printf("\nQuick Sort\n");
            printf("Time: %lld ticks\n", time);
            printf("Iterations: %d\n", ITERATION);
            printf("Avarage time: %lld ticks\n", time / ITERATION);
        }
        // sort2
        if (menu1 == 4)
        {
            // sort
            unsigned long long time = 0;
            for (int i = 0; i < ITERATION; ++i)
            {
                // copy
                key_sort_t *key_sort = (key_sort_t *)malloc( sizeof(key_sort_t) * cur_cnt );
                for (int i = 0; i < cur_cnt; ++i)
                {
                    key_sort[i].index = i;
                    key_sort[i].height = students[i].height;
                }
                unsigned long long tmp_time = tick();
                sort2(key_sort, cur_cnt);
                time += tick() - tmp_time;
                free(key_sort);
            }
            printf("\nSort\n");
            printf("Time: %lld ticks\n", time);
            printf("Iterations: %d\n", ITERATION);
            printf("Avarage time: %lld ticks\n", time / ITERATION);
            // qsort
            time = 0;
            for (int i = 0; i < ITERATION; ++i)
            {
                // copy
                key_sort_t *key_sort = (key_sort_t *)malloc( sizeof(key_sort_t) * cur_cnt );
                for (int i = 0; i < cur_cnt; ++i)
                {
                    key_sort[i].index = i;
                    key_sort[i].height = students[i].height;
                }
                unsigned long long tmp_time = tick();
                sort2_q(key_sort, cur_cnt);
                time += tick() - tmp_time;
                free(key_sort);
            }
            printf("\nQuick Sort\n");
            printf("Time: %lld ticks\n", time);
            printf("Iterations: %d\n", ITERATION);
            printf("Avarage time: %lld ticks\n", time / ITERATION);
        }
        // print
        if (menu1 == 5)
        {
            // print
            printf("\n");
            if (cur_cnt == 0)
                printf("No element in array!\n");
            for (int i = 0; i < cur_cnt; ++i)
            {
                printf("\nIndex: %d\n", i + 1);
                print_student(&students[i]);
            }
        }
        // print hostel
        int cnt = 0;
        if (menu1 == 6)
        {
            // print
            for (int i = 0; i < cur_cnt; ++i)
            {
                if (students[i].digs == HOSTEL)
                {
                    cnt++;
                    printf("\n");
                    print_student(&students[i]);
                }
            }
            if (cnt == 0)
                printf("No element in array!\n");
        }
        if (menu1 == 7)
        {
            char fname[MAX_PATH] = "";
            printf("\nFile name: ");
            scanf("%255s", &fname[0] );
            FILE *f = fopen(fname, "r");
            if (!f)
            {
                printf("File not found!\n");
                break;
            }
            int num = 0;
            fscanf(f, "%d\n", &num);
            for (int i = 0; i < num; ++i)
            {
                if (cur_cnt >= max_cnt)
                {
                    max_cnt <<= 1;
                    student_t *tmp = (student_t *)malloc( sizeof(student_t) * max_cnt );
                    if (!tmp)
                    {
                        return 1;
                    }
                    for (int i = 0; i < cur_cnt; ++i)
                    {
                        tmp[i] = students[i];
                    }
                    free(students);
                    students = tmp;
                }
                input_student(&students[cur_cnt++], f);
            }
            fclose(f);
        }
    }
    while( menu1 != 8 );
    // free mem
    free(students);
    return EXIT_SUCCESS;
}
