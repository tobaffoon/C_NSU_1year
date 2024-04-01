#include <stdio.h>
#include <stdlib.h>

#define NIL -1
#define INFINITY (LONG_LONG_MAX>>1)

typedef struct Request{
	long long fst,
		snd;
} Request;

//info about where does the edge go and what weight it has
typedef struct Edge{
	long long to,
			weight;
} Edge;

//growing array
typedef struct Incident {
	long long n, cap;
	Edge *edges;
} Incident;

typedef struct Vector{
	long long n, cap;
	long long *arr;
} Vector;

enum Visited{
	not_visited,
	visited
};

typedef struct Vertex {
	long long d,
			pr_id;         //predecessor's id in shortest path (real vertex id, not -1)
	enum Visited visit;
	Incident incident; //Incident numbers
} Vertex;

typedef struct Graph {
	Vertex *vertices;
	long long v_num;          //number of vertices
	long long v_unvisited;
} Graph;

void Incident_push(Incident *ls, long long to, long long weight) {
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

void Vector_push(Vector *ls, long long val) {
	if (ls->cap == 0) {
		ls->cap = 2;
		ls->arr = malloc(sizeof(long long) * ls->cap);
	}
	if (ls->n == ls->cap) {
		ls->cap *= 2;
		ls->arr = (long long *) realloc(ls->arr, sizeof(long long) * ls->cap);
	}
	ls->arr[ls->n++] = val;
}

long long Extract_min(Graph *graph){
	long long min = INFINITY,
			min_id = -1;
	for(int i = 0; i < graph->v_num; i++) {
		if(graph->vertices[i].d < min && graph->vertices[i].visit == not_visited){
			min = graph->vertices[i].d;
			min_id = i;
		}
	}
	graph->v_unvisited--;
	graph->vertices[min_id].visit = visited;
	return min_id;
}

//relax (u,v) edge, supposing the input is correct + push new value to the priority queue
void Relax(Graph graph, long long u, Edge v){
	//v.d > u.d + w(u,v)
	if(graph.vertices[v.to].d > graph.vertices[u].d + v.weight){
		graph.vertices[v.to].d = graph.vertices[u].d + v.weight;
		graph.vertices[v.to].pr_id = u;
	}
}

void Dijkstra_init(Graph graph, long long from) {
	for(int i = 0; i < graph.v_num; i++) {
		graph.vertices[i].d = INFINITY;
		graph.vertices[i].pr_id = NIL;
		graph.vertices[i].visit = not_visited;
	}
	graph.vertices[from].d = 0;
}

void Dijkstra(Graph graph, long long from) {
	Dijkstra_init(graph, from);
	graph.v_unvisited = graph.v_num - 1;
	long long u,      //current vertex
	adj_num;    //number of vertices adjacent to u
	//i.e. queue is not empty
	while(graph.v_unvisited != 0) {
		u = Extract_min(&graph);
		//if no vertices have been left unvisited
		if(u == -1){
			return;
		}
		adj_num = graph.vertices[u].incident.n;
		for(int i = 0; i < adj_num; i++) {
			//relax(u, v) for some adjacent v
			Relax(graph, u, graph.vertices[u].incident.edges[i]);
		}
	}
}

void Print_shortest_path(Graph graph, long long from, long long to, FILE *out){
	if(graph.vertices[to].d == INFINITY){
		fprintf(out, "NO\n");
		return;
	}
	fprintf(out, "YES  %lld ", graph.vertices[to].d);
	Vector path = {0, 0, 0};
	while(to != from){
		Vector_push(&path, to + 1);
		to = graph.vertices[to].pr_id;
	}
	Vector_push(&path, from + 1);
	fprintf(out, " %lld ", path.n);
	for(int i = path.n - 1; i >= 0; i--) {
		fprintf(out, " %lld", path.arr[i]);
	}
	fprintf(out, "\n");
	free(path.arr);
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
	long long edges_num,       //number if edges
		path_requests;
	fscanf(fi, "%lld %lld %lld", &(graph.v_num), &edges_num, &path_requests);
	graph.vertices = calloc(graph.v_num, sizeof(Vertex));
	Request *requests = malloc(path_requests * sizeof(Request));

	long long from, to, weight;
	for(int i = 0; i < path_requests; i++) {
		fscanf(fi, "%lld %lld", &from, &to);
		requests[i].fst = from;
		requests[i].snd = to;
	}
	for(int i = 0; i < edges_num; i++) {
		fscanf(fi, "%lld %lld %lld", &from, &to, &weight);
		Incident_push(&(graph.vertices[from - 1].incident), to - 1, weight);
		Incident_push(&(graph.vertices[to - 1].incident), from - 1, weight);
	}
	for(int i = 0; i < path_requests; i++) {
		Dijkstra(graph, requests[i].fst - 1);
		Print_shortest_path(graph, requests[i].fst - 1, requests[i].snd - 1, fo);
	}
	Graph_free(&graph);
	free(requests);
	fclose(fi);
	fclose(fo);
	return 0;
}