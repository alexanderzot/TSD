#include "libgraph.h"

node_graph *Graph::create_node_graph(vertex_t vertex, distance_t distance)
{
    node_graph *tmp = (node_graph *)malloc( sizeof(node_graph) );
    tmp->distance = distance;
    tmp->vertex = vertex;
    tmp->next = NULL;
    return tmp;
}

vertex_t Graph::city_get_cnt(void)
{
    return this->city_cnt;
}

int Graph::is_city(const char *name)
{
    for (register vertex_t i = 0; i < this->city_cnt; ++i)
    {
        if (strcmp(name, city_name[i]) == 0)
            return 1;
    }
    return 0;
}

void Graph::city_add(const char *name)
{
    // add elements
    if (city_cnt == city_size)
    {
        //printf("ADD MEM\n");
        this->city_size = this->city_size == 0 ? BEGIN_SIZE : this->city_size << 1;
        this->city_name = (char **)realloc(this->city_name, sizeof(char *) * this->city_size);
        this->graph_list = (node_graph **)realloc(this->graph_list, sizeof(node_graph *) * this->city_size);
        for (register vertex_t i = this->city_cnt; i < this->city_size; ++i)
        {
            this->city_name[i] = NULL;
            this->graph_list[i] = NULL;
        }
    }
    this->city_name[this->city_cnt++] = strdup(name);
}

vertex_t Graph::city_get_index(const char *name)
{
    for (register vertex_t i = 0; i < this->city_cnt; ++i)
    {
        if (strcmp(name, city_name[i]) == 0)
            return i;
    }
    return -1;
}

const char *Graph::city_get_name(vertex_t index)
{
    if (index >= this->city_cnt)
        return NULL;
    return this->city_name[index];
}

void Graph::print_city(void)
{
    printf("City count: %d\n", this->city_cnt);
    printf("City size: %d\n", this->city_size);
    for (register vertex_t i = 0; i < this->city_cnt; ++i)
        printf(" > %s\n", this->city_name[i]);
    printf("\n");
}

Graph::Graph(void)
{
    // City
    this->city_name = NULL;
    this->city_cnt = 0;
    this->city_size = 0;

    this->graph_list = NULL;
}

Graph::~Graph(void)
{
    for (register vertex_t i = 0; i < this->city_cnt; ++i)
    {
        free(this->city_name[i]);

        node_graph *node = this->graph_list[i];
        while (node)
        {
            node_graph *tmp = node;
            node = tmp->next;
            free(tmp);
        }
    }
    free(this->city_name);
    free(this->graph_list);
}

int Graph::graph_add_edge(vertex_t city1_index, vertex_t city2_index, distance_t distance)
{
    if (city1_index >= this->city_cnt || city1_index >= this->city_cnt)
        return -1;

    node_graph *city1_node = this->graph_list[city1_index];
    node_graph *city2_node = this->graph_list[city2_index];

    node_graph *tmp;

    tmp = this->graph_list[city1_index];
    this->graph_list[city1_index] = create_node_graph(city2_index, distance);
    this->graph_list[city1_index]->next = tmp;

    tmp = this->graph_list[city2_index];
    this->graph_list[city2_index] = create_node_graph(city1_index, distance);
    this->graph_list[city2_index]->next = tmp;
}

int Graph::graph_add_edge(const char *city1, const char *city2, distance_t distance)
{
    // add citys 1
    if (!this->is_city(city1))
        this->city_add(city1);
    // add citys 2
    if (!this->is_city(city2))
        this->city_add(city2);

    vertex_t city1_index = this->city_get_index(city1);
    vertex_t city2_index = this->city_get_index(city2);

    if (city1_index == -1 || city2_index == -1)
        return -2;

    return this->graph_add_edge(city1_index, city2_index, distance);
}

int Graph::graph_remove_edge(vertex_t city1_index, vertex_t city2_index)
{
    if (city1_index >= this->city_cnt || city1_index >= this->city_cnt)
        return -1;

    node_graph *city1_node = this->graph_list[city1_index];
    if (city1_node && city1_node->vertex == city2_index)
    {
        node_graph *tmp = this->graph_list[city1_index];
        this->graph_list[city1_index] = city1_node->next;
        free(tmp);
    }
    else
    {
        while (city1_node && city1_node->next->vertex != city2_index)
            city1_node = city1_node->next;
        if (city1_node)
        {
            node_graph *tmp = city1_node->next;
            city1_node->next = city1_node->next->next;
            free(tmp);
        }
    }

    node_graph *city2_node = this->graph_list[city2_index];
    if (city2_node && city2_node->vertex == city1_index)
    {
        node_graph *tmp = this->graph_list[city2_index];
        this->graph_list[city2_index] = city2_node->next;
        free(tmp);
    }
    else
    {
        while (city2_node && city2_node->next->vertex != city1_index)
            city2_node = city2_node->next;
        if (city2_node)
        {
            node_graph *tmp = city2_node->next;
            city2_node->next = city2_node->next->next;
            free(tmp);
        }
    }
    return 0;
}

distance_t Graph::graph_get_distance(vertex_t city1_index, vertex_t city2_index)
{
    if (city1_index >= this->city_cnt || city2_index >= this->city_cnt)
        return 0;
    node_graph *node = this->graph_list[city1_index];
    while (node && node->vertex != city2_index)
    {
        node = node->next;
    }

    if (node)
        return node->distance;
    return 0;
}

void Graph::graph_print(void)
{
    for (register vertex_t i = 0; i < this->city_cnt; ++i)
    {
        node_graph *node = this->graph_list[i];
        printf("From %s to ", this->city_get_name(i));
        while (node)
        {
            printf("%s(%llu)", this->city_get_name(node->vertex), node->distance);
            if (node->next)
                printf(", ");
            else
                printf(".");
            node = node->next;
        }
        printf("\n");
    }
}

void Graph::graph_print_gv(const char *file,
                           int cnt,
                           vertex_t from,
                           vertex_t to1,
                           vertex_t to2,
                           vertex_t to3)
{
    FILE *f = fopen(file, "w");
    fprintf(f, "graph City{\n");

    for (register vertex_t i = 0; i < this->city_cnt; ++i)
    {
        for (register vertex_t j = i + 1; j < this->city_cnt; ++j)
        {
            if (i == j)
                continue;
            distance_t d = this->graph_get_distance(i, j);
            if (d > 0)
            {
                fprintf(f, "\t\"%s\"--\"%s\";\n",
                        this->city_get_name(i),
                        this->city_get_name(j),
                        this->graph_get_distance(i, j));
            }
        }
    }
    switch (cnt)
    {
    case 3:
        fprintf(f, "\t\"%s\"--\"%s\" [color=red];\n", this->city_get_name(from), this->city_get_name(to3));
    case 2:
        fprintf(f, "\t\"%s\"--\"%s\" [color=red];\n", this->city_get_name(from), this->city_get_name(to2));
    case 1:
        fprintf(f, "\t\"%s\"--\"%s\" [color=red];\n", this->city_get_name(from), this->city_get_name(to1));
    }
    fprintf(f, "}");
    fclose(f);
}

int Graph::graph_path(vertex_t root, distance_t all_min)
{
     vertex_t size = this->city_cnt;
     //vertex_t a[size][size]; // матрица связей
     vertex_t d[size]; // минимальное расстояние
     int v[size]; // посещенные вершины
     vertex_t temp;
     vertex_t minindex, min;

     //Инициализация
     for(register vertex_t i = 0; i < size; i++)
     {
         d[i] = 10000; // результат - кратчайшее расстояние
         v[i] = 1; // Прсещение вершны?
     }
     d[root] = 0; // begin


     // Шаг алгоритма
     do
     {
         minindex = 10000;
         min = 10000;
         // Поиск минимальной непосещенной вершины
         for(register vertex_t i = 0; i < size; i++)
         {
            if ((v[i] == 1) && (d[i]<min))
            {
                 min = d[i];
                 minindex = i;
            }
        }
        if (minindex != 10000)
        {
            for(register vertex_t i = 0; i < size; ++i)
            {
                //if (this->graph_get_distance(minindex, i)  a[minindex][i] > 0)
                if (this->graph_get_distance(minindex, i) > 0)
                {
                    temp = min + this->graph_get_distance(minindex, i);
                    if (temp < d[i])
                        d[i] = temp;
                }
            }
            v[minindex] = 0;
        }
    }
    while(minindex < 10000);

    // Вывод матрицы связей
    for (register vertex_t i = 0; i < size; ++i)
    {
        if (d[i] > all_min)
             return 0;
    //    printf("%s: %d\n", this->city_get_name(i), d[i]);
    }

    return 1;
}

int Graph::run_alg(vertex_t root, distance_t all_min)
{
    if (this->graph_path(root, all_min))
    {
        this->graph_print_gv("out.txt", 0, root, 0, 0, 0);
        return 1;
    }

    // 1 edge add
    for (register vertex_t i = 0; i < this->city_cnt; ++i)
    {
        if (i == root)
            continue;
        this->graph_add_edge(root, i, 1);
        if (this->graph_path(root, all_min))
        {
            this->graph_remove_edge(root, i);
            this->graph_print_gv("out.txt", 1, root, i, 0, 0);
            return 1;
        }
        this->graph_remove_edge(root, i);
    }

    // 2 edge add
    for (register vertex_t i = 0; i < this->city_cnt; ++i)
    {
        if (i == root)
            continue;
        this->graph_add_edge(root, i, 1);
        for (register vertex_t j = i + 1; j < this->city_cnt; ++j)
        {
            if (j == root)
                continue;
            this->graph_add_edge(root, j, 1);
            if (this->graph_path(root, all_min))
            {
                this->graph_remove_edge(root, i);
                this->graph_remove_edge(root, j);
                this->graph_print_gv("out.txt", 2, root, i, j, 0);
                return 1;
            }
            this->graph_remove_edge(root, j);
        }
        this->graph_remove_edge(root, i);
    }

    // 3 edge add
    for (register vertex_t i = 0; i < this->city_cnt; ++i)
    {
        if (i == root)
            continue;
        this->graph_add_edge(root, i, 1);
        for (register vertex_t j = i + 1; j < this->city_cnt; ++j)
        {
            if (j == root)
                continue;
            this->graph_add_edge(root, j, 1);

            for (register vertex_t k = j + 1; k < this->city_cnt; ++k)
            {
                if (k == root)
                    continue;
                this->graph_add_edge(root, k, 1);
                if (this->graph_path(root, all_min))
                {
                    this->graph_remove_edge(root, i);
                    this->graph_remove_edge(root, j);
                    this->graph_remove_edge(root, k);
                    this->graph_print_gv("out.txt", 3, root, i, j, k);
                    return 1;
                }
                this->graph_remove_edge(root, k);
            }
            this->graph_remove_edge(root, j);
        }
        this->graph_remove_edge(root, i);
    }

    FILE *f = fopen("out.txt", "w");
    fprintf(f, "No solve!\n");
    fclose(f);

    return 0;
}
