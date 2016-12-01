#include <iostream>

#include "libio.h"
#include "libtree.h"
#include "libdyn.h"

#include <vector>
#define MAX_LEN 255

using namespace std;

unsigned long long tick(void)
{
    unsigned long long d;
    __asm__ __volatile__ ("rdtsc" : "=A" (d) );
    return d;
}

void test_tree(FILE *f, char ch)
{
    CTree tree;

    int err = 0;
    char *line = read_line(f, &err);
    char *buf = (char *)malloc( sizeof(char) * 255 );
    while (!err)
    {
		size_t len = strlen(line);
		size_t pos = 0;
		for (int i = 0; i < len + 1; ++i)
		{
			// new word
			if (line[i] == ' ' || line[i] == '\n' || line[i] == '\t' || line[i] == '\0')
			{
				buf[pos] = '\0';
				// if that is word
				if (pos > 0)
				{
					// if not in list then add it
					tree.insert( strdup(buf) );
				}
				pos = 0;
			}
			else
				buf[pos++] = line[i];
		}
        free(line);
        line = read_line(f, &err);
    }
    tree.print();
    unsigned long long time = tick();
    time = tick() - time;
    tree.remove_char(ch);
    tree.print();
    cout << "Time remove tree: " << time << " ticks" <<  endl;
    return;
}

void test_dyn_array(FILE *f, char ch)
{
    CDyn arr;

    int err = 0;
    char *line = read_line(f, &err);
    char *buf = (char *)malloc( sizeof(char) * 255 );
    while (!err)
    {
		size_t len = strlen(line);
		size_t pos = 0;
		for (int i = 0; i < len + 1; ++i)
		{
			// new word
			if (line[i] == ' ' || line[i] == '\n' || line[i] == '\t' || line[i] == '\0')
			{
				buf[pos] = '\0';
				// if that is word
				if (pos > 0)
				{
					// if not in list then add it
					arr.insert( strdup(buf) );
				}
				pos = 0;
			}
			else
				buf[pos++] = line[i];
		}
        free(line);
        line = read_line(f, &err);
    }
    unsigned long long time = tick();
    arr.remove_char(ch);
    time = tick() - time;
    cout << "Time remove dynam array: " << time << " ticks" << endl;
    return;
}

int menu_value(void)
{
    int value = 0;
    int flag = 0;
    do
    {
        flag = 0;
        cout << "Input: ";
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
    int menu = 0;
    CTree tree;
    do
    {
        //print menu
        cout << endl << ">Main menu:" << endl;
        cout << " [0]: Load from file" << endl;
        cout << " [1]: Add element" << endl;
        cout << " [2]: Remove element" << endl;
        cout << " [3]: Search element" << endl;
        cout << " [4]: Print tree" << endl;
        cout << " [5]: Tests" << endl;
        cout << " [6]: Exit" << endl;
        // input
        do
        {
            menu = menu_value();
        }
        while (menu < 0 || menu > 6);

        cout << endl;
        if (menu == 0)
        {
            char str[MAX_LEN] = "";
            do
            {
                cout << "File name: ";
                cin >> str;
            }
            while( strlen(str) == 0 );
            // open file
            cout << endl;
            FILE *f = fopen(str, "r");
            if (!f)
            {
                cout << "File not found!" << endl;
                continue;
            }
            // read file
            int err = 0;
            char *line = read_line(f, &err);
            char *buf = (char *)malloc( sizeof(char) * 255 );
            while (!err)
            {
                size_t len = strlen(line);
                size_t pos = 0;
                for (int i = 0; i < len + 1; ++i)
                {
                    // new word
                    if (line[i] == ' ' || line[i] == '\n' || line[i] == '\t' || line[i] == '\0')
                    {
                        buf[pos] = '\0';
                        // if that is word
                        if (pos > 0)
                        {
                            // if not in list then add it
                            tree.insert( strdup(buf) );
                        }
                        pos = 0;
                    }
                    else
                        buf[pos++] = line[i];
                }
                free(line);
                line = read_line(f, &err);
            }
            cout << "Load from file finished!" << endl;
            fclose(f);
        }
        else if (menu == 1)
        {
            char str[MAX_LEN] = "";
            int flag = 0;
            do
            {
                flag = 0;
                cout << "Input word: ";
                flag = scanf("%s", &str);
                // read all chars
                char ch;
                while( scanf("%c", &ch) && ch != '\n' )
                    flag = 0;
            }
            while( flag == 0 || strlen(str) == 0 || strstr(str, " ") > 0  );
            // insert
            cout << endl;
            unsigned long long time = tick();
            tree.insert( strdup(str) );
            time = tick() - time;
            cout << "Insert to tree is done!" << endl;
            cout << "Time: " << time << " ticks" << endl;
        }
        else if (menu == 2)
        {
            if (tree.is_empty())
            {
                cout << "Tree is empty!" << endl;
                continue;
            }

            char str[MAX_LEN] = "";
            int flag = 0;
            do
            {
                flag = 0;
                cout << "Input word: ";
                flag = scanf("%s", &str);
                // read all chars
                char ch;
                while( scanf("%c", &ch) && ch != '\n' )
                    flag = 0;
            }
            while( flag == 0 || strlen(str) == 0 || strstr(str, " ") > 0  );

            // remove
            cout << endl;
            unsigned long long time = tick();
            if (tree.remove(str))
            {
                cout << "Element is removed from tree!" << endl;
            }
            else
            {
                cout << "Element not found in tree!" << endl;
            }
            cout << "Time: " << tick() - time << " ticks" <<  endl;
        }
        else if (menu == 3)
        {
            // read string
            char str[MAX_LEN] = "";
            int flag = 0;
            do
            {
                flag = 0;
                cout << "Input word: ";
                flag = scanf("%s", &str);
                // read all chars
                char ch;
                while( scanf("%c", &ch) && ch != '\n' )
                    flag = 0;
            }
            while( flag == 0 || strlen(str) == 0 || strstr(str, " ") > 0  );
            // search
            unsigned long long time = tick();
            node *p = tree.search(str);
            time = tick() - time;
            cout << endl;
            if (!p)
            {
                cout << "Element not found!" << endl;
            }
            else
            {
                cout << "Adress: " << p << endl;
                cout << "Value: " << p->value << endl;
            }
            cout << "Time: " << time << " ticks" << endl;
        }
        else if (menu == 4)
        {
            cout << endl;
            cout << "View tree:" << endl;
            tree.print();
        }
        else if (menu == 5)
        {
            char str[MAX_LEN] = "";
            do
            {
                cout << "File name: ";
                cin >> str;
            }
            while( strlen(str) == 0 );
            char ch[MAX_LEN] = "";
            do
            {
                cout << "Input char: ";
                cin >> ch;
            }
            while( strlen(ch) != 1 );
            FILE *f;
            // Tree
            f = fopen(str, "r");
            test_tree(f, ch[0]);
            fclose(f);
            // Dyn
            f = fopen(str, "r");
            test_dyn_array(f, ch[0]);
            fclose(f);
        }
    }
    while (menu != 6);

    /*
    FILE *f = NULL;

    f = fopen("test3.txt", "r");
    unsigned long long time1 = tick();
    test_tree(f);
    cout << "time: " << tick() - time1 << endl;
    fclose(f);

    f = fopen("test3.txt", "r");
    unsigned long long time2 = tick();
    test_dyn_array(f);
    cout << "time: " << tick() - time2 << endl;
    fclose(f);
    */

    return 0;
}
