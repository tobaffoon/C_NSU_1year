#include <stdio.h>
#include <stdlib.h>

#define D(from, to) graph.ds[(from) * graph.v_num + (to)]
#define I(from, to) graph.prs[(from) * graph.v_num + (to)]
#define NIL -1
#define INFINITY (INT_MAX>>1)

typedef struct Graph {
	unsigned int *ds;
	int v_num;          //number of vertices
	int *prs;           //predecessors in shortest path algorithm
} Graph;

typedef struct Path{
	int n,
		cap,
		*path;
} Path;

void Path_push(Path *path, int num) {
	if (path->cap == 0) {
		path->cap = 2;
		path->path = malloc(sizeof(int) * path->cap);
	}
	if (path->n == path->cap) {
		path->cap *= 2;
		path->path = (int *) realloc(path->path, sizeof(int) * path->cap);
	}
	path->path[path->n++] = num;
}

void Floyd_Warshall(Graph graph) {
	for(int w = 0; w < graph.v_num; w++) {
		for(int u = 0; u < graph.v_num; u++) {
			for(int v = 0; v < graph.v_num; v++) {
				if(D(u, v) > D(u, w) + D(w, v)){
					D(u, v) = D(u, w) + D(w, v);
					I(u, v) = w;
				}
			}
		}
	}
}

void Recurs_path(Graph graph, int from, int to, Path *path){
	if(from == to){
		Path_push(path, from + 1);
		return;
	}
	Recurs_path(graph, from, I(from, to), path);
	if(I(from, to) != from){
		Recurs_path(graph, I(from, to), to, path);
	}
}

void Print_shortest_path(Graph graph, int from, int to, FILE *out){
	Path path = {0, 0, 0};
	Recurs_path(graph, from, to, &path);
	Path_push(&path, to + 1);
	fprintf(out, " %d ", path.n);
	for(int i = 0; i < path.n; i++) {
		fprintf(out, " %d", path.path[i]);
	}
}

void Graph_free(Graph graph) {
	free(graph.ds);
	free(graph.prs);
}

int main() {
	FILE *fi = fopen("input.txt", "r"),
			*fo = fopen("output.txt", "w");
	Graph graph;
	int edges_num,       //number of edges
	path_requests,
			time_requests;
	fscanf(fi, "%d %d %d %d", &(graph.v_num), &edges_num, &path_requests, &time_requests);
	graph.ds = calloc(graph.v_num * graph.v_num, sizeof(unsigned int));
	graph.prs = calloc(graph.v_num * graph.v_num, sizeof(int));


	for(int i = 0; i < graph.v_num; i++) {
		for(int j = 0; j < graph.v_num; j++) {
			D(i, j) = INFINITY;
			I(i, j) = NIL;
		}
		D(i, i) = 0;
	}

	int from, to, weight;
	for(int i = 0; i < edges_num; i++) {
		fscanf(fi, "%d %d %d", &from, &to, &weight);
		if(D(from - 1, to - 1) > weight){
			D(from - 1, to - 1) = weight;
			I(from - 1, to - 1) = from - 1;
			D(to - 1, from - 1) = weight;
			I(to - 1, from - 1) = to - 1;
		}
	}
	Floyd_Warshall(graph);
	for(int i = 0; i < path_requests; i++) {
		fscanf(fi, "%d %d", &from, &to);
		fprintf(fo, "%d ", D(from - 1, to - 1));
		Print_shortest_path(graph, from - 1, to - 1, fo);
		fprintf(fo, "\n");
	}
	for(int i = 0; i < time_requests; i++) {
		fscanf(fi, "%d %d", &from, &to);
		fprintf(fo, "%d", D(from - 1, to - 1));
		fprintf(fo, "\n");
	}
	Graph_free(graph);
	fclose(fi);
	fclose(fo);
	return 0;
}