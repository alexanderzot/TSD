#include "libtree.h"
#include "bin_libtree.h"
#include "hash_close.h"
#include "hash_open.h"
#include <vector>

#define MAX_LEN 255

using namespace std;

unsigned long long tick(void)
{
    unsigned long long d;
    __asm__ __volatile__ ("rdtsc" : "=A" (d) );
    return d;
}

int main()
{
    //printf("%u\n", get_pred_simple(15) );
    //printf("%u\n", get_next_simple(15) );
    /*HashClose hc(10);
    printf("CLOSE\n");
    printf("add: %d\n", hc.add("test1"));
    printf("add: %d\n",hc.add("test2"));
    printf("add: %d\n",hc.add("test3"));
    printf("add: %d\n",hc.add("test4"));
    printf("add: %d\n",hc.add("test5"));
    printf("add: %d\n",hc.add("test6"));
    printf("add: %d\n",hc.add("test7"));

    printf("add: %d\n",hc.add("test8"));

    /*printf("add: %d\n",hc.add("test9"));
    printf("add: %d\n",hc.add("test10"));
    printf("add: %d\n",hc.add("lolka"));

    hc.print();

    printf("find: %s\n", hc.find("test8") );

    return 0;
    */

    vector <char *>vector_w;
    unsigned long long int t;

    int menu = 0;
    do
    {
        //print menu
        cout << endl << ">Main menu:" << endl;
        cout << " [1]: Load from file" << endl;
        cout << " [2]: Write words" << endl;
        cout << " [3]: Print tree" << endl;
        cout << " [4]: Print hash-close" << endl;
        cout << " [5]: Print hash-open" << endl;
        cout << " [6]: Time search and memory test" << endl;
        cout << " [7]: Print tree" << endl;
        cout << " [9]: Exit" << endl;
        // input
        do
        {
            menu = menu_value();
        }
        while (menu < 1 || menu > 7 && menu != 9);

        cout << endl;
        if (menu == 1)
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
            char *buf = (char *)malloc( sizeof(char) * MAX_LEN );
            while (!err)
            {
                size_t len = strlen(line);
                size_t pos = 0;
                for (int i = 0; i < len + 1; ++i)
                {
                    // new word
                    if (line[i] == ' ' || line[i] == '\n' || line[i] == '\t' || line[i] == '\0' ||
                        line[i] == ',' || line[i] == '.' || line[i] == '!' || line[i] == '?')
                    {
                        buf[pos] = '\0';
                        // if that is word
                        if (pos > 0)
                        {
                            // if not in list then add it
                            //tree.insert( strdup(buf) );
                            vector_w.push_back( strdup(buf) );
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
        else if (menu == 2)
        {
            if (vector_w.size() == 0)
            {
                printf("No words!\n");
                continue;
            }

            for(unsigned int i = 0; i < vector_w.size(); i++)
                cout << i + 1 << ") " << vector_w[i] << endl;
        }
        else if (menu == 3)
        {
            if (vector_w.size() == 0)
            {
                printf("No words!\n");
                continue;
            }

            CTree tree;
            for(unsigned int i = 0; i < vector_w.size(); i++)
                tree.insert( strdup(vector_w[i]) );
            tree.print();
        }
        else if (menu == 4)
        {
            if (vector_w.size() == 0)
            {
                printf("No words!\n");
                continue;
            }

            HashClose hc(vector_w.size());
            for(unsigned int i = 0; i < vector_w.size(); i++)
                hc.insert( strdup(vector_w[i]) );
            hc.print();
        }
        else if (menu == 5)
        {
            if (vector_w.size() == 0)
            {
                printf("No words!\n");
                continue;
            }

            HashOpen ho(vector_w.size());
            for(unsigned int i = 0; i < vector_w.size(); i++)
                ho.insert( strdup(vector_w[i]) );
            ho.print();
        }
        else if (menu == 6)
        {
            if (vector_w.size() == 0)
            {
                printf("No words!\n");
                continue;
            }

            char val_str[MAX_PATH]= "";
            do
            {
                cout << "Value for search: ";
                cin >> val_str;
            }
            while( strlen(val_str) == 0 );

            // tree
            CTree tree;
            for(unsigned int i = 0; i < vector_w.size(); i++)
                tree.insert( strdup(vector_w[i]) );
            t = tick();
            node *tmp = tree.search(val_str);
            printf("\nTime tree AVL: %llu ticks\n", tick() - t);
            printf("Value: %s\n", tmp ? tmp->value : "not found!");
            printf("Memory: %d bytes\n", tree.get_memory());
            printf("Compare: %d\n\n", tree.get_cmp());

            // tree bin
            CTreeBin tree_bin;
            for(unsigned int i = 0; i < vector_w.size(); i++)
                tree_bin.insert( strdup(vector_w[i]) );
            t = tick();
            node_bin *tmp2 = tree_bin.search(val_str);
            printf("Time tree-bin: %llu ticks\n", tick() - t);
            printf("Value: %s\n", tmp2 ? tmp2->value : "not found!");
            printf("Memory: %d bytes\n", tree_bin.get_memory());
            printf("Compare: %d\n\n", tree_bin.get_cmp());

            // hash close
            HashClose hc(vector_w.size());
            for(unsigned int i = 0; i < vector_w.size(); i++)
                hc.insert( strdup(vector_w[i]) );
            t = tick();
            char *tmp_str1 = hc.search(val_str);
            printf("Time hash-close: %llu ticks\n", tick() - t);
            printf("Value: %s\n", tmp_str1 ? tmp_str1 : "not found!");
            printf("Memory: %d bytes\n", hc.get_memory());
            printf("Compare: %d\n\n", hc.get_cmp());

            // hash open
            HashOpen ho(vector_w.size());
            for(unsigned int i = 0; i < vector_w.size(); i++)
                ho.insert( strdup(vector_w[i]) );
            t = tick();
            char *tmp_str2 = ho.search(val_str);
            printf("Time hash-open: %llu ticks\n", tick() - t);
            printf("Value: %s\n", tmp_str2 ? tmp_str2 : "not found!");
            printf("Memory: %d bytes\n", ho.get_memory());
            printf("Compare: %d\n\n", ho.get_cmp());
        }
        else if (menu == 7)
        {
            if (vector_w.size() == 0)
            {
                printf("No words!\n");
                continue;
            }

            CTreeBin tree;
            for(unsigned int i = 0; i < vector_w.size(); i++)
                tree.insert( strdup(vector_w[i]) );
            tree.print();
        }
    }
    while (menu != 9);
    return 0;
}
