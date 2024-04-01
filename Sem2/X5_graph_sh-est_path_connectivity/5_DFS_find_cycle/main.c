#include <stdio.h>
#include <stdlib.h>

//growing array
typedef struct Incident {
    int n,
            cap,
            *ns;
} Incident;

enum Mark {
    Black,
    Grey,
    White
};

typedef struct Vertex {
    enum Mark mark;
    Incident incident; //Incident numbers
} Vertex;

typedef struct Graph {
    Vertex *vertices;
    int n_num;          //number of vertices
} Graph;

typedef struct Cycle {
    int *vs;
    char is_cycle;
    int length;
} Cycle;

void Dfs(Graph *graph, int start, Cycle *array) {
    static char stop_cycle = 0;
    if (graph->vertices[start].mark != White)
        return;

	graph->vertices[start].mark = Grey;
    for (int i = 0; i < graph->vertices[start].incident.n; i++) {
        if (graph->vertices[graph->vertices[start].incident.ns[i]].mark == Grey) {
            array->is_cycle = 1;
            array->vs[array->length++] = graph->vertices[start].incident.ns[i] + 1;
            return;
        }
	    Dfs(graph, graph->vertices[start].incident.ns[i], array);
        //to pass is_Cycle through recursion + include vertices
        if (array->is_cycle == 1) {
            //if we have reached the beginning
            if(graph->vertices[start].incident.ns[i] + 1 == array->vs[0]){
                stop_cycle = 1;
            }
            if(stop_cycle == 0) {
                array->vs[array->length++] = graph->vertices[start].incident.ns[i] + 1;
            }
            return;
        }
    }
	graph->vertices[start].mark = Black;
}

void Find_cycle(Graph *graph, Cycle *array) {
    for (int i = 0; i < graph->n_num; i++) {
        array->length=0;
	    Dfs(graph, i, array);
        if (array->is_cycle) {
            return;
        }
    }
}

void Incident_push(Incident *ls, int num) {
    if (ls->cap == 0) {
        ls->cap = 2;
        ls->ns = malloc(sizeof(int) * ls->cap);
    }
    if (ls->n == ls->cap) {
        ls->cap *= 2;
        ls->ns = (int *) realloc(ls->ns, sizeof(int) * ls->cap);
    }
    ls->ns[ls->n++] = num;
}

void Graph_free(Graph *graph) {
    for (int i = 0; i < graph->n_num; i++) {
        if (graph->vertices[i].incident.cap != 0) {
            free(graph->vertices[i].incident.ns);
        }
    }
    free(graph->vertices);
}

int main() {
    FILE *fi = fopen("input.txt", "r"),
            *fo = fopen("output.txt", "w");
    Graph graph;
    int edges_num;       //number if edges
    fscanf(fi, "%d %d", &(graph.n_num), &edges_num);
    Cycle cycle;
    cycle.vs = malloc(graph.n_num * sizeof(int));
    cycle.is_cycle = 0;
	graph.vertices = calloc(graph.n_num, sizeof(Vertex));
    for (int i = 0; i < graph.n_num; i++) {
	    graph.vertices[i].mark = White;
    }

    int from, to;
    for (int i = 0; i < edges_num; i++) {
        fscanf(fi, "%d %d", &from, &to);
        Incident_push(&(graph.vertices[to - 1].incident), from - 1);
    }

	Find_cycle(&graph, &cycle);
    if (cycle.is_cycle) {
        fprintf(fo, "%d\n", cycle.length);
        for (int i = 0; i < cycle.length; i++) {
            fprintf(fo, "%d ", cycle.vs[i]);
        }
    } else {
        fprintf(fo, "-1");
    }
    Graph_free(&graph);
    free(cycle.vs);
    fclose(fi);
    fclose(fo);
    return 0;
}
