#include <stdio.h>
#include <stdlib.h>

#define NIL -1
#define INFINITY (INT_MAX>>1)

//info about where does the edge go and what weight it has
typedef struct Edge{
	int to,
			weight;
} Edge;

//growing array
typedef struct Incident {
	int n, cap;
	Edge *edges;
} Incident;

typedef struct Vector{
	int n, cap;
	int *arr;
} Vector;

typedef struct Vertex {
	int d,
			pr_id;         //predecessor's id in shortest path (real vertex id, not -1)
	Incident incident; //Incident numbers
} Vertex;

typedef struct Graph {
	Vertex *vertices;
	int v_num;          //number of vertices
} Graph;

void Incident_push(Incident *ls, int to, int weight) {
	if (ls->cap == 0) {
		ls->cap = 2;
		ls->edges = malloc(sizeof(Edge) * ls->cap);
	}
	if (ls->n == ls->cap) {
		ls->cap *= 2;
		ls->edges = (Edge *) realloc(ls->edges, sizeof(Edge) * ls->cap);
	}
	ls->edges[ls->n].to = to;
	ls->edges[ls->n++].weight = weight;
}

void Vector_push(Vector *ls, int val) {
	if (ls->cap == 0) {
		ls->cap = 2;
		ls->arr = malloc(sizeof(Edge) * ls->cap);
	}
	if (ls->n == ls->cap) {
		ls->cap *= 2;
		ls->arr = (Edge *) realloc(ls->arr, sizeof(Edge) * ls->cap);
	}
	ls->arr[ls->n++] = val;
}

//relax (u,v) edge, supposing the input is correct + push new value to the priority queue
void Relax(Graph graph, int u, Edge v){
	//v.d > u.d + w(u,v)
	if(graph.vertices[v.to].d > graph.vertices[u].d + v.weight){
		graph.vertices[v.to].d = graph.vertices[u].d + v.weight;
		graph.vertices[v.to].pr_id = u;
	}
}

void Bellman_Ford_init(Graph graph, int from) {
	//Pqueue_push(head, graph, int from);
	for(int i = 0; i < graph.v_num; i++) {
		graph.vertices[i].d = INFINITY;
		graph.vertices[i].pr_id = NIL;
	}
	graph.vertices[from].d = 0;
}

void Bellman_Ford(Graph graph, int from) {
	Bellman_Ford_init(graph, from);
	int adj_num;    //number of vertices adjacent to u
	for(int i = 1; i < graph.v_num; i++) {
		for(int j = 0; j < graph.v_num; j++) {
			adj_num = graph.vertices[j].incident.n;
			for(int k = 0; k < adj_num; k++) {
				Relax(graph, j, graph.vertices[j].incident.edges[k]);
			}
		}
	}
}

void Print_shortest_path(Graph graph, int from, int to, FILE *out){
	Vector path = {0, 0, 0};
	while(to != from){
		Vector_push(&path, to + 1);
		to = graph.vertices[to].pr_id;
	}
	Vector_push(&path, from + 1);
	fprintf(out, " %d ", path.n);
	for(int i = path.n - 1; i >= 0; i--) {
		fprintf(out, " %d", path.arr[i]);
	}
	fprintf(out, "\n");
}

void Graph_free(Graph *graph) {
	for(int i = 0; i < graph->v_num; i++) {
		free(graph->vertices[i].incident.edges);
	}
	free(graph->vertices);
}

int main() {
	FILE *fi = fopen("input.txt", "r"),
			*fo = fopen("output.txt", "w");
	Graph graph;
	int edges_num,       //number of edges
	path_requests;
	fscanf(fi, "%d %d %d", &(graph.v_num), &edges_num, &path_requests);
	graph.vertices = calloc(graph.v_num, sizeof(Vertex));
	int *requests = malloc(path_requests * sizeof(int));

	int from, to, weight;
	for(int i = 0; i < path_requests; i++) {
		fscanf(fi, "%d", &to);
		requests[i] = to - 1;
	}

	for(int i = 0; i < edges_num; i++) {
		fscanf(fi, "%d %d %d", &from, &to, &weight);
		Incident_push(&(graph.vertices[from - 1].incident), to - 1, weight);
	}
	Bellman_Ford(graph, 0);
	for(int i = 0; i < path_requests; i++) {
		fprintf(fo, "%d ", graph.vertices[requests[i]].d);
		Print_shortest_path(graph, 0, requests[i], fo);
	}
	Graph_free(&graph);
	fclose(fi);
	fclose(fo);
	return 0;
}