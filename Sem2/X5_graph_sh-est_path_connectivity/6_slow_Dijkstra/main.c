#include <stdio.h>
#include <stdlib.h>

#define NIL -1
#define INFINITY (INT_MAX>>1)

enum Visited{
		not_visited,
		visited
};

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

typedef struct Vertex {
	int d,
			pr_id;         //predecessor's id in shortest path (real vertex id, not -1)
	enum Visited visit;
	Incident incident; //Incident numbers
} Vertex;

typedef struct Graph {
	Vertex *vertices;
	int v_num;          //number of vertices
	int v_unvisited;
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

int Extract_min(Graph *graph){
	int min = INFINITY,
		min_id = -1;
	for(int i = 0; i < graph->v_num; i++) {
		if(graph->vertices[i].d < min && graph->vertices[i].visit == not_visited){
			min = graph->vertices[i].d;
			min_id = i;
		}
	}
	graph->v_unvisited--;
	return min_id;
}

//relax (u,v) edge, supposing the input is correct + push new value to the priority queue
void Relax(Graph graph, int u, Edge v){
	//v.d > u.d + w(u,v)
	if(graph.vertices[v.to].d > graph.vertices[u].d + v.weight){
		graph.vertices[v.to].d = graph.vertices[u].d + v.weight;
		graph.vertices[v.to].pr_id = u;
	}
}

void Dijkstra_init(Graph graph, int from) {
	for(int i = 0; i < graph.v_num; i++) {
		graph.vertices[i].d = INFINITY;
		graph.vertices[i].pr_id = NIL;
		graph.vertices[i].visit = not_visited;
	}
	graph.vertices[from].d = 0;
}

void Dijkstra(Graph graph, int from) {
	Dijkstra_init(graph, from);
	graph.v_unvisited = graph.v_num;
	int u,      //current vertex
	adj_num;    //number of vertices adjacent to u
	//i.e. queue is not empty
	while(graph.v_unvisited != 0) {
		u = Extract_min(&graph);
		graph.vertices[u].visit = visited;
		adj_num = graph.vertices[u].incident.n;
		for(int i = 0; i < adj_num; i++) {
			//relax(u, v) for some adjacent v
			Relax(graph, u, graph.vertices[u].incident.edges[i]);
		}
	}
}

void Print_shortest_path(Graph graph, int from, int to, FILE *out){
	int path[300];  //max number of edges is 300
	int path_length = 0;
	while(graph.vertices[to].pr_id != from){
		path[path_length++] = to + 1;
		to = graph.vertices[to].pr_id;
	}
	path[path_length++] = to + 1; //second vertex
	path[path_length++] = graph.vertices[to].pr_id + 1; //start vertex
	fprintf(out, " %d ", path_length);
	for(int i = path_length - 1; i >= 0; i--) {
		fprintf(out, " %d", path[i]);
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
	fscanf(fi, "%d %d %d %d", &(graph.v_num), &edges_num, &path_requests);
	graph.vertices = calloc(graph.v_num, sizeof(Vertex));
	int *requests = malloc(path_requests * sizeof(int));

	int from, to, weight;
	for(int i = 0; i < path_requests; i++) {
		fscanf(fi, "%d", &to);
		requests[i] = to;
	}

	for(int i = 0; i < edges_num; i++) {
		fscanf(fi, "%d %d %d", &from, &to, &weight);
		Incident_push(&(graph.vertices[from - 1].incident), to - 1, weight);
		Incident_push(&(graph.vertices[to - 1].incident), from - 1, weight);
	}
	Dijkstra(graph, 0);
	//I FUCKING BROKE IT, DOESN'T WORK AT ALL
	Graph_free(&graph);
	fclose(fi);
	fclose(fo);
	return 0;
}