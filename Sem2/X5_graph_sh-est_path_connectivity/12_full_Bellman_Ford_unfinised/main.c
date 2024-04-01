#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

//info about where does the edge go and what weight it has
typedef struct Edge{
	int to;
	int64_t weight;
} Edge;

//growing array
typedef struct Incident {
	int n, cap;
	Edge *edges;
} Incident;

typedef struct Vertex {
	int64_t d;
	Incident incident; //Incident numbers
} Vertex;

typedef struct Graph {
	Vertex *vertices;
	char *is_neg_cycle;
	char *is_unreach;
	int v_num;          //number of vertices
	int e_num;          //number of edges
} Graph;

void Incident_push(Incident *ls, int64_t to, int64_t weight) {
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

//relax (u,v) edge, supposing the input is correct + push new value to the priority queue
void Relax(Graph graph, int u, Edge v){
	//v.d > u.d + w(u,v)
	if(graph.is_unreach[u]){
		return;
	}
	if(graph.is_unreach[v.to] || graph.vertices[v.to].d > graph.vertices[u].d + v.weight){
		graph.vertices[v.to].d = graph.vertices[u].d + v.weight;
		graph.is_unreach[v.to] = 0;
	}
}

void Bellman_Ford_init(Graph graph, int from) {
	for(int i = 0; i < graph.v_num; i++) {
		graph.is_unreach[i] = 1;
		graph.vertices[i].incident.n=0;
		graph.vertices[i].incident.cap=0;
	}
	graph.vertices[from].d = 0;
	graph.is_unreach[from] = 0;
}

void Bellman_Ford(Graph graph) {
	int adj_num;    //number of vertices adjacent to u
	for(int i = 1; i < graph.v_num; i++) {
		for(int j = 0; j < graph.v_num; j++) {
			adj_num = graph.vertices[j].incident.n;
			for(int k = 0; k < adj_num; k++) {
				Relax(graph, j, graph.vertices[j].incident.edges[k]);
			}
		}
	}
	Edge e;
	for(int j = 0; j < graph.v_num; j++) {
		adj_num = graph.vertices[j].incident.n;
		for(int k = 0; k < adj_num; k++) {
			e = graph.vertices[j].incident.edges[k];
			if(graph.vertices[e.to].d > graph.vertices[j].d + e.weight){
				graph.is_neg_cycle[e.to] = 1;
				graph.vertices[e.to].d = graph.vertices[j].d + e.weight;
			}
		}
	}
	for(int j = 0; j < graph.v_num; j++) {
		if(graph.is_neg_cycle[j] == 1) {
			adj_num = graph.vertices[j].incident.n;
			for(int k = 0; k < adj_num; k++) {
				e = graph.vertices[j].incident.edges[k];
				if(graph.vertices[e.to].d > graph.vertices[j].d + e.weight) {
					graph.is_neg_cycle[e.to] = 1;
				}
			}
		}
	}
}

void Graph_free(Graph *graph) {
	for(int i = 0; i < graph->v_num; i++) {
		if(graph->vertices[i].incident.cap!=0) {
			free(graph->vertices[i].incident.edges);
		}
	}
	free(graph->vertices);
	free(graph->is_unreach);
	free(graph->is_neg_cycle);
}

int main() {
	FILE *fi = fopen("input.txt", "r"),
			*fo = fopen("output.txt", "w");
	Graph graph;
	int start;
	fscanf(fi, "%d %d %d", &(graph.v_num), &(graph.e_num), &start);
	graph.vertices = malloc(graph.v_num * sizeof(Vertex));
	graph.is_neg_cycle = calloc(graph.v_num, 1);
	graph.is_unreach = malloc(graph.v_num);
	Bellman_Ford_init(graph, start - 1);

	int from, to;
	int64_t weight;
	for(int i = 0; i < graph.e_num; i++) {
		fscanf(fi, "%d %d %lld", &from, &to, &weight);
		Incident_push(&(graph.vertices[from - 1].incident), to - 1, weight);
	}
	Bellman_Ford(graph);
	for(int i = 0; i < graph.v_num; i++) {
		if(graph.is_unreach[i]){
			fprintf(fo, "*\n");
		}
		else if(graph.is_neg_cycle[i]){
			fprintf(fo, "-\n");
		}
		else fprintf(fo, "%lld\n", graph.vertices[i].d);
	}
	Graph_free(&graph);
	fclose(fi);
	fclose(fo);
	return 0;
}