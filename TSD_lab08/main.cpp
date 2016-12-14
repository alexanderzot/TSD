#include <iostream>
#include <stdlib.h>
#include <stdio.h>

#include "libgraph.h"

using namespace std;

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
    Graph g;

    char tmp[MAX_PATH] = "";
    do
    {
        cout << endl << ">Main menu:" << endl;
        cout << " [1]: Add edge" << endl;
        cout << " [2]: Remove edge" << endl;
        cout << " [3]: Show graph" << endl;
        cout << " [4]: Run Alg and show" << endl;
        cout << " [5]: Exit" << endl;
        menu = menu_value();

        if (menu == 1)
        {
            char city1[MAX_PATH] = "";
            char city2[MAX_PATH] = "";
            unsigned long long int dist = 0;


            cout << "\nCity name 1: ";
            cin >> city1;
            cout << "City name 2: ";
            cin >> city2;

            g.graph_add_edge(city1, city2, 1);
        }
        else if (menu == 2)
        {
            // remove
            char city1[MAX_PATH] = "";
            char city2[MAX_PATH] = "";
            cout << "\nCity name 1: ";
            cin >> city1;
            cout << "City name 2: ";
            cin >> city2;
            vertex_t city1_index = g.city_get_index(city1);
            vertex_t city2_index = g.city_get_index(city2);
            if (city1_index == -1 || city2_index == -1)
                printf("\nEdge not found!\n");
            else
            {
                printf("\nEdge removed\n");
                g.graph_remove_edge(city1_index, city2_index);
            }
        }
        else if (menu == 3)
        {
            // show
            g.graph_print_gv("out.txt", 0, 0, 0, 0, 0);
            system("C:/GraphViz/bin/dot -Tpng out.txt -o out.png");
            system("out.png");
        }
        else if (menu == 4)
        {
            // alg
            char city[MAX_PATH] = "";
            cout << "City-root name: ";
            cin >> city;

            vertex_t root = g.city_get_index(city);

            if (root != -1)
            {
                unsigned long long int dist = 0;
                cout << "Distantion min-path: ";
                cin >> dist;
                if (dist != 0 && g.run_alg(root, dist))
                {
                    system("C:/GraphViz/bin/dot -Tpng out.txt -o out.png");
                    system("out.png");
                }
                else
                    printf("\nNo solve!\n");
            }
            else
                printf("\nRoot City not found!\n");
        }
    }
    while(menu != 5);
    return EXIT_SUCCESS;
}
