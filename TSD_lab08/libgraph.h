#ifndef LIBGRAPH_H_INCLUDED
#define LIBGRAPH_H_INCLUDED

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define BEGIN_SIZE 1

typedef unsigned long long int vertex_t;

typedef unsigned long long int distance_t;

typedef struct node_graph
{
    vertex_t vertex;
    distance_t distance;
    struct node_graph *next;
} node_graph;


class Graph
{
private:
    char **city_name;
    vertex_t city_cnt;
    vertex_t city_size;
    node_graph **graph_list;
    node_graph *create_node_graph(vertex_t vertex, distance_t distance);
public:
    Graph(void);
    ~Graph(void);
    vertex_t city_get_cnt(void);
    int is_city(const char *name);
    void city_add(const char *name);
    vertex_t city_get_index(const char *name);
    const char *city_get_name(vertex_t index);
    void print_city(void);
    int graph_add_edge(const char *city1, const char *city2, distance_t distance);
    int graph_add_edge(vertex_t city1_index, vertex_t city2_index, distance_t distance);
    int graph_remove_edge(vertex_t city1, vertex_t city2);
    distance_t graph_get_distance(vertex_t city1_index, vertex_t city2_index);
    void graph_print(void);
    void graph_print_gv(const char *file, int cnt, vertex_t, vertex_t, vertex_t, vertex_t);
    int graph_path(vertex_t root, distance_t all_min);
    int run_alg(vertex_t root, distance_t all_min);
};



#endif // LIBGRAPH_H_INCLUDED
