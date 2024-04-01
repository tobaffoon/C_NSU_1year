#include <stdio.h>
#include <stdlib.h>

typedef struct Incident {
    int n,
        cap,
        *vs;
} Incident;

enum Visited{
    visited = 0,
    not_visited = 1
};

typedef struct Vertex{
    enum Visited visited;
    int BFS_depth;
    Incident inc_vert; //incident vertices
} Vertex;

typedef struct Graph{
    Vertex *vertices;
    int v_num;          //number of vertices
} Graph;

typedef struct Queue{
    int first,
        last,
        *arr;
} Queue;

void push_q(Queue *queue, int v) {
    queue->arr[queue->last++] = v;
}

//push all incident vertices of v and mark them in graph
void push_inc(Graph *graph, Queue *queue, Vertex v){
    for (int i = 0; i < v.inc_vert.n; i++) {
        if(graph->vertices[v.inc_vert.vs[i]].visited == not_visited) {
            push_q(queue, v.inc_vert.vs[i]);
            graph->vertices[v.inc_vert.vs[i]].visited = visited;
            graph->vertices[v.inc_vert.vs[i]].BFS_depth = v.BFS_depth + 1;
        }
    }
}

int pop_q(Queue *queue){
    return queue->arr[queue->first++];
}

void BFS_SH_PTH(Graph *graph){
    Queue queue;
    queue.arr = calloc(graph->v_num, sizeof(int));
    queue.first = 0;
    queue.last = 0;

    graph->vertices[0].visited = visited;
    push_inc(graph, &queue, graph->vertices[0]);
    int cur_id = pop_q(&queue);

    //while queue is not empty
    while(cur_id != 0){
        push_inc(graph, &queue, graph->vertices[cur_id]);   //push and mark incident vertices
        cur_id = pop_q(&queue);
    }

    free(queue.arr);
}

//add new incident vertex (edge = (from, to))
void vert_push(Incident *from, int to) {
    if (from->cap == 0) {
        from->cap = 2;
        from->vs = malloc(sizeof(int) * from->cap);
    }
    if (from->n == from->cap) {
        from->cap *= 2;
        from->vs = (int *) realloc(from->vs, sizeof(int) * from->cap);
    }
    from->vs[from->n++] = to;
}

void init_graph(Graph *g){
    g->vertices = malloc(g->v_num * sizeof(Vertex));
    for (int i = 0; i < g->v_num; i++) {
        g->vertices[i].visited = not_visited;
        g->vertices[i].BFS_depth = -1;          //until any edge is discovered every vertex is unreachable from 1
        g->vertices[i].inc_vert.cap = 0;
        g->vertices[i].inc_vert.n = 0;
    }
    g->vertices[0].BFS_depth = 0;               //path from 1 to 1 takes 0 edges
}

void free_graph(Graph *g){
    for (int i = 0; i < g->v_num; i++) {
        if(g->vertices[i].inc_vert.cap != 0){
            free(g->vertices[i].inc_vert.vs);
        }
    }
    free(g->vertices);
}

int main() {
    FILE    *fi = fopen("input.txt", "r"),
            *fo = fopen("output.txt", "w");

    int edge_number;        //number of edges
    Graph graph;

    fscanf(fi, "%d %d", &graph.v_num, &edge_number);
    init_graph(&graph);
    int temp_from, temp_to;
    for (int i = 0; i < edge_number; i++) {
        fscanf(fi,"%d %d", &temp_from, &temp_to);
        vert_push(&(graph.vertices[temp_from-1].inc_vert), temp_to - 1);
    }

    BFS_SH_PTH(&graph);

    for (int i = 0; i < graph.v_num; i++) {
        fprintf(fo, "%d\n", graph.vertices[i].BFS_depth);
    }
    free_graph(&graph);
    fclose(fi);
    fclose(fo);
    return 0;
}