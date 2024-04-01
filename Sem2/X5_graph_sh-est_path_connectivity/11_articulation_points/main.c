#include <stdio.h>
#include <stdlib.h>

#define MIN(A, B) ((A)<=(B)?(A):(B))
#define NIL 0
#define TREE 1

#define BLACK 2
#define GREY 1
#define WHITE 0

typedef int (*my_comp)(const void *, const void *);

int q_comp(const void *a, const void *b) {
	return (*(int *) a - *(int *) b);
}

typedef struct Edge {
	int to,
			in_id;
} Edge;

typedef struct Incident {
	int n,
			cap;
	Edge *ns;
} Incident;

typedef struct Vertex {
	char mark;
	int level,         //depth in DFS
	up;            //up level in DFS
	Incident incident; //Incident numbers
} Vertex;

typedef struct Graph {
	Vertex *vertices;   //array of all the vertices
	int v_num;          //number of vertices
	int e_num;          //number of edges
	int* articlations;    //list of bridges
	int art_n;
	char *types;    //types of edges by in_id (1 => tree, 0 => back/no edge)
	char *is_art;   //avoid multiple articulation points (0=>no, 1=>yes)
} Graph;

void Incident_push(Incident *ls, int num, int id) {
	if(ls->cap == 0) {
		ls->cap = 2;
		ls->ns = malloc(sizeof(Edge) * ls->cap);
	}
	if(ls->n == ls->cap) {
		ls->cap *= 2;
		ls->ns = (Edge *) realloc(ls->ns, sizeof(Edge) * ls->cap);
	}
	ls->ns[ls->n].to = num;
	ls->ns[ls->n++].in_id = id;
}

void DFS_init(Graph *graph) {
	for(int i = 0; i < graph->v_num; i++) {
		graph->vertices[i].mark = WHITE;
		graph->vertices[i].incident.n = 0;
		graph->vertices[i].incident.cap = 0;
	}
	graph->types = calloc(graph->e_num, 1);
	graph->is_art = calloc(graph->v_num, 1);
	graph->articlations = malloc(graph->v_num * sizeof(int));
	graph->art_n = 0;
}

void DFS(Graph *graph, int start) {
	graph->vertices[start].mark = GREY;
	int adj_num = graph->vertices[start].incident.n;    //number of incident edges
	int to_v;
	for(int i = 0; i < adj_num; i++) {
		to_v = graph->vertices[start].incident.ns[i].to;
		if(graph->vertices[to_v].mark == WHITE){
			if(graph->vertices[start].level == 0 && i > 0 && graph->is_art[start] != 1){
				graph->articlations[graph->art_n++] = start;
				graph->is_art[start] = 1;
			}
			graph->types[graph->vertices[start].incident.ns[i].in_id] = TREE;
			graph->vertices[to_v].level = graph->vertices[start].level + 1;
			graph->vertices[to_v].up = graph->vertices[to_v].level;
			DFS(graph, to_v);
			graph->vertices[start].up = MIN(graph->vertices[start].up, graph->vertices[to_v].up);
			if(graph->vertices[start].level != 0 && graph->vertices[to_v].up >= graph->vertices[start].level &&
					   graph->is_art[start] != 1) {
				graph->articlations[graph->art_n++] = start;
				graph->is_art[start] = 1;
			}
		}
		else if(graph->vertices[to_v].mark == GREY && graph->types[graph->vertices[start].incident.ns[i].in_id] != TREE){
			graph->vertices[start].up = MIN(graph->vertices[start].up, graph->vertices[to_v].level);
		}
	}
	graph->vertices[start].mark = BLACK;
}

void Graph_free(Graph *graph) {
	free(graph->articlations);
	for(int i = 0; i < graph->v_num; i++) {
		if(graph->vertices[i].incident.cap != 0) {
			free(graph->vertices[i].incident.ns);
		}
	}
	free(graph->vertices);
}

int main() {
	FILE *fi = fopen("input.txt", "r"),
			*fo = fopen("output.txt", "w");
	Graph graph;
	int from, to;

	fscanf(fi, "%d %d", &(graph.v_num), &(graph.e_num));
	graph.vertices = malloc(graph.v_num * sizeof(Vertex));
	DFS_init(&graph);

	for(int i = 0; i < graph.e_num; i++) {
		fscanf(fi, "%d %d", &from, &to);
		Incident_push(&(graph.vertices[from - 1].incident), to - 1, i);
		Incident_push(&(graph.vertices[to - 1].incident), from - 1, i);
	}

	for(int i = 0; i < graph.v_num; i++) {
		if(graph.vertices[i].mark == WHITE) {
			graph.vertices[i].level = 0;
			graph.vertices[i].up = 0;
			DFS(&graph, i);
		}
	}

	my_comp q_func = &q_comp;
	qsort((void *) graph.articlations, graph.art_n, sizeof(int), q_func);
	fprintf(fo, "%d\n", graph.art_n);
	for(int i = 0; i < graph.art_n; i++) {
		fprintf(fo, "%d ", graph.articlations[i] + 1);
	}

	Graph_free(&graph);
	fclose(fi);
	fclose(fo);
	return 0;
}
