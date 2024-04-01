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
	int color;
    Incident incident; //Incident numbers
} Vertex;

typedef struct Graph {
    Vertex *vertices;
    int v_num;          //number of vertices
} Graph;

typedef struct Tout{
	int *arr,
		n,
		cur_color;
}Tout;

void DFS_init(Graph *graph){
    for(int i = 0; i < graph->v_num; i++) {
        graph->vertices[i].mark = White;
    }
}

void Dfs_fst(Graph *graph, int start, Tout *tout) {
	graph->vertices[start].mark = Grey;
    for (int i = 0; i < graph->vertices[start].incident.n; i++) {
        if(graph->vertices[graph->vertices[start].incident.ns[i]].mark == White){
            Dfs_fst(graph, graph->vertices[start].incident.ns[i], tout);
		}
    }
    tout->arr[tout->n++] = start;
	graph->vertices[start].mark = Black;
}

void Dfs_snd(Graph *graph, int start, Tout *tout) {
	graph->vertices[start].mark = Grey;
	graph->vertices[start].color = tout->cur_color;
	for (int i = 0; i < graph->vertices[start].incident.n; i++) {
		if(graph->vertices[graph->vertices[start].incident.ns[i]].mark == White){
			Dfs_snd(graph, graph->vertices[start].incident.ns[i], tout);
		}
	}
	graph->vertices[start].mark = Black;
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

int Incident_pop(Incident *ls) {
	if(ls->n == 0){
		return -1;
	}
	if(ls->n == 1){
		int k = ls->ns[0];
		ls->n = 0;
		ls->cap = 0;
		free(ls->ns);
		return k;
	}
	return ls->ns[--ls->n];
}

void Reverse_graph(Graph *graph){
	int adj_num,
		cv;
	Incident *new_incidence = calloc(graph->v_num, sizeof(Incident));
	for(int i = 0; i < graph->v_num; i++) {
		adj_num = graph->vertices[i].incident.n;
		for(int j = 0; j < adj_num; j++) {
			cv = Incident_pop(&(graph->vertices[i].incident));
			Incident_push(&(new_incidence[cv]), i);
		}
	}
	//replace old incidences with new ones (as Incident_pop frees previous arrays, we can just replace pointers)
	for(int i = 0; i < graph->v_num; i++) {
		graph->vertices[i].incident = new_incidence[i];
	}
	free(new_incidence);
}

void Graph_free(Graph *graph) {
    for (int i = 0; i < graph->v_num; i++) {
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
    fscanf(fi, "%d %d", &(graph.v_num), &edges_num);
	graph.vertices = calloc(graph.v_num, sizeof(Vertex));
    for (int i = 0; i < graph.v_num; i++) {
	    graph.vertices[i].mark = White;
    }

    int from, to;
    for (int i = 0; i < edges_num; i++) {
        fscanf(fi, "%d %d", &from, &to);
        Incident_push(&(graph.vertices[from - 1].incident), to - 1);
    }
	Tout tout;
	tout.arr = calloc(graph.v_num, sizeof(int));
	tout.n = 0;
	//get all touts in graph
	DFS_init(&graph);
	for(int i = 0; i < graph.v_num; i++) {
		if(graph.vertices[i].mark == White){
			Dfs_fst(&graph, i, &tout);
		}
	}
	//reverse edges
	Reverse_graph(&graph);

	//evaluate colours of Vertices (SCC - strongly connected component)
	tout.cur_color = 0;
	DFS_init(&graph);
	int last_tout;
	for (int i = tout.n - 1; i >= 0; i--) {
		last_tout = tout.arr[i];
		if(graph.vertices[last_tout].mark == White){
			Dfs_snd(&graph, last_tout, &tout);
			tout.cur_color++;
		}
	}

	//print SCCs
	fprintf(fo, "%d\n", tout.cur_color);
	for(int i = 0; i < graph.v_num; i++) {
		fprintf(fo, "%d ", graph.vertices[i].color + 1);
	}
	free(tout.arr);
    Graph_free(&graph);
    fclose(fi);
    fclose(fo);
    return 0;
}
