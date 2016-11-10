#include <iostream>

#include "queue_array.h"
#include "queue_list.h"

#define INSERT_POS 4

using namespace std;

template <typename T>
void test(void)
{
    std::cout << "Begin test" << endl;
    T qarr;
    request r;
    request t;

    // push
    r.type = 1;
    qarr.push_end( r );
    qarr.print();

    // pop
    t = qarr.pop_front();
    std::cout << "pop value: " << t.type << std::endl;
    qarr.print();

    // push
    r.type = 2;
    qarr.push_end( r );
    qarr.print();

    // push
    r.type = 3;
    qarr.push_end( r );
    qarr.print();

    // push
    r.type = 4;
    qarr.push_end( r );
    qarr.print();

    // push
    r.type = 5;
    qarr.push_end( r );
    qarr.print();

    // pop
    t = qarr.pop_front();
    std::cout << "pop value: " << t.type << std::endl;
    qarr.print();

    // pop
    t = qarr.pop_front();
    std::cout << "pop value: " << t.type << std::endl;
    qarr.print();

    // push
    r.type = 6;
    qarr.push_end( r );
    qarr.print();

    // push
    r.type = 7;
    qarr.push_end( r );
    qarr.print();

    // push
    r.type = 8;
    qarr.push_end( r );
    qarr.print();

    // push
    r.type = 9;
    qarr.push_end( r );
    qarr.print();

    std::cout << std::endl;
}

double get_time(time_interval t)
{
    return (double)(t.to - t.from) * rand() / RAND_MAX + t.from;
}

template <typename T>
void run_alg(int interval, time_interval ti1, time_interval ti2, time_interval ti3, unsigned n, bool ignore_t3 = false, bool show_mem = false)
{
    // request
    request req;
    // queue
    T queue;
    if (ignore_t3)
        req.type = 1;
    else
        req.type = 2;
    queue.push_end(req);
    // request_info
    request_info info;
    info.model_time = 0.0;
    info.stay_time = 0.0;
    info.obrab_time = 0.0;
    info.type_in1 = 0;
    info.type_in2 = 0;
    info.type_out1 = 0;
    info.type_out2 = 0;
    info.error_flag = 0;
    if (req.type == 1)
        info.type_in1++;
    else
        info.type_in2++;
   // time
    double t1 = 0.0;
    double t23 = 0.0;
    double tmin;
    // other
    int show = 0;
    clock_t time_clock = clock();
    while (info.type_out1 < n)
    {
        if (t1 == 0.0)
            t1 = get_time(ti1);
        if (t23 == 0.0)
            t23 = get_time(ti2);

        tmin = min(t1, t23);
        info.model_time += tmin;

        // push element
        if (tmin == t1 && tmin)
        {
            t1 = 0.0;
            t23 -= tmin;
            req.type = 1;
            info.type_in1++;
            if (!queue.push_end(req))
            {
                info.error_flag = 1;
                return;
            }
        }
        // pop element
        if (tmin == t23 && tmin)
        {
            t1 -= tmin;
            if (queue.is_empty())
            {
                info.stay_time += tmin;
                continue;
            }
            t23 = 0.0;
            req = queue.pop_front();
            if (req.type == 1)
            {
                info.type_out1++;
            }
            else if (req.type == 2)
            {
                info.type_out2++;
                req.type = 2;
                info.type_in2++;
                if (!queue.insert_pos(req, INSERT_POS))
                {
                    info.error_flag = 1;
                    return;
                }
                t23 = get_time(ti3);
            }
        }

        // out
        if (info.type_out1 % interval == 0 && info.type_out1 != show)
        {
            show = info.type_out1;
            info.obrab_time = info.model_time - info.stay_time;
            cout << "[" << info.type_out1 / interval << "]:" << endl;
            cout << " Size: " << queue.get_size() << endl;
            cout << " In:   " << info.type_in2 + info.type_in1 << endl;
            cout << " Out:  " << info.type_out2 + info.type_out1 << endl;
            cout << " Avar: " << info.obrab_time / (info.type_in1 + info.type_in2) << endl << endl;
        }
    }
    info.obrab_time = info.model_time - info.stay_time;
    if (!info.error_flag)
    {
        cout << " Work time: " << clock() - time_clock << endl;
        cout << "Model time: " << info.model_time << endl;
        cout << "Obrab time: " << info.obrab_time << endl;
        cout << " Stay time: " << info.stay_time << endl;
        cout << " In type-1: " << info.type_in1 << endl;
        cout << " In type-2: " << info.type_in2 << endl;
        cout << "Out type-1: " << info.type_out1 << endl;
        cout << "Out type-2: " << info.type_out2 << endl;
        if (show_mem)
        {
            cout << "Show free memory: ";
            int flag;
            cin >> flag;
            if (flag)
            {
                queue.free_print();
            }
        }
    }
    else
    {
        cout << "Memory allocated error!" << endl;
    }
}

int menu_value(void)
{
    int value = 0;
    int flag = 0;
    do
    {
        flag = 0;
        printf("Input: ");
        flag = scanf("%1d", &value);
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
    srand( time(0) );
    int menu1 = 0;
    // setting
    time_interval t1 = {0, 5}, t2 = {0, 4}, t3 = {0, 4};
    bool ign_t3 = false;
    unsigned int interval = 100;
    unsigned int count = 1000;
    do
    {
        //print menu
        printf("\n>Main menu:\n");
        printf(" [0]: Show setting\n");
        printf(" [1]: Edit setting\n");
        printf(" [2]: Modelling array\n");
        printf(" [3]: Modelling list\n");
        printf(" [4]: Exit\n");
        // input
        do
        {
            menu1 = menu_value();
        }
        while (menu1 < 0 || menu1 > 4);

        if (menu1 == 0)
        {
            cout << endl << "===== Setting =====" << endl;
            cout << " Interval: " << interval << endl;
            cout << " Count: " << count << endl;
            cout << " Ignore T3: " << ign_t3 << endl;
            cout << " T1 ---------------" << endl;
            cout << "  from: " << t1.from << endl;
            cout << "  to:   " << t1.to << endl;
            cout << " T2 ---------------" << endl;
            cout << "  from: " << t2.from << endl;
            cout << "  to:   " << t2.to << endl;
            cout << " T3 ---------------" << endl;
            cout << "  from: " << t3.from << endl;
            cout << "  to:   " << t3.to << endl;
            cout << "===================" << endl;
        }
        else if (menu1 == 1)
        {
            cout << endl << "==== Set setting ====" << endl;
            cout << " Interval[" << interval << "]: ";
            cin >> interval;
            cout << " Count[" << count << "]: ";
            cin >> count;
            cout << " Ignore T3[" << ign_t3 << "]: ";
            cin >> ign_t3;
            cout << " T1 -----------------" << endl;
            cout << "  from[" << t1.from << "]: ";
            cin >> t1.from;
            cout << "  to[" << t1.to << "]:   ";
            cin >> t1.to;
            cout << " T2 -----------------" << endl;
            cout << "  from[" << t2.from << "]: ";
            cin >> t2.from;
            cout << "  to[" << t2.to << "]:   ";
            cin >> t2.to;
            cout << " T3 -----------------" << endl;
            cout << "  from[" << t3.from << "]: ";
            cin >> t3.from;
            cout << "  to[" << t3.to << "]:   ";
            cin >> t3.to;
            cout << "=====================" << endl;
        }
        else if (menu1 == 2)
        {
            run_alg<Queue_array>(interval, t1, t2, t3, count, ign_t3, false);
        }
        else if (menu1 == 3)
        {
            run_alg<Queue_list>(interval, t1, t2, t3, count, ign_t3, true);
        }
    }
    while (menu1 != 4);
    return 0;
}
