#include <stdio.h>
#include <stdlib.h>

#define MIN(A, B) ((A)<=(B)?(A):(B))
#define NIL 0
#define UNDIRECT 1
#define MULTIPLE 2
#define TREE 3
#define BACK 4
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
	char type;
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
	int* bridges;    //list of bridges
	int br_n;
} Graph;

void Incident_push(Incident *ls, int num, int id) {
	//Multiple edges check
	for(int i = 0; i < ls->n; i++) {
		if(ls->ns[i].to == num) {
			ls->ns[i].type = MULTIPLE;
			return;
		}
	}
	if(ls->cap == 0) {
		ls->cap = 2;
		ls->ns = malloc(sizeof(Edge) * ls->cap);
	}
	if(ls->n == ls->cap) {
		ls->cap *= 2;
		ls->ns = (Edge *) realloc(ls->ns, sizeof(Edge) * ls->cap);
	}
	ls->ns[ls->n].to = num;
	ls->ns[ls->n].in_id = id;
	ls->ns[ls->n++].type = UNDIRECT;
}

void Incident_del(Incident *ls, int to) {
	if(ls->cap == 0) {
		return;
	}
	for(int i = 0; i < ls->n; i++) {
		if(ls->ns[i].to == to) {
			ls->ns[i].type = NIL;
			return;
		}
	}
}

void DFS_init(Graph *graph) {
	for(int i = 0; i < graph->v_num; i++) {
		graph->vertices[i].mark = WHITE;
		graph->vertices[i].incident.n = 0;
		graph->vertices[i].incident.cap = 0;
	}
	graph->bridges = malloc(graph->v_num * sizeof(int));
	graph->br_n = 0;
}

void DFS(Graph *graph, int start) {
	graph->vertices[start].mark = GREY;
	int adj_num = graph->vertices[start].incident.n;
	int u;        //current vertex
	//hanging vertex check
	if(adj_num == 1) {
		u = graph->vertices[start].incident.ns[0].to;
		if(graph->vertices[u].mark == BLACK) {
			return;
		}

		if(graph->vertices[start].incident.ns[0].type != MULTIPLE) {
			graph->bridges[graph->br_n++] = graph->vertices[start].incident.ns[0].in_id;
		}
		graph->vertices[start].level = graph->v_num;
		graph->vertices[start].up = graph->v_num - 1;
		graph->vertices[start].mark = BLACK;
		return;
	}
	Edge *pe;     //current edge
	for(int i = 0; i < adj_num; i++) {
		pe = &(graph->vertices[start].incident.ns[i]);
		u = pe->to;
		//do anything only if there is an edge
		//there cannot be a tree edge because any tree edge is created below
		if(pe->type == UNDIRECT) {
			//Orient and classify an incident edge
			if(graph->vertices[u].mark == WHITE) {
				graph->vertices[u].level = graph->vertices[start].level + 1;
				graph->vertices[u].up = graph->vertices[u].level;
				//if it's multiple in the last if we want to presume this state
				pe->type = TREE;
				Incident_del(&(graph->vertices[u].incident), start);
				DFS(graph, u);
				//min from other up values
				graph->vertices[start].up = MIN(graph->vertices[start].up, graph->vertices[u].up);
				//after (start, i) edge was calculated, we can determine if it's a bridge
				if(graph->vertices[u].up >= graph->vertices[u].level) {
					graph->bridges[graph->br_n++] =  pe->in_id;
				}
			}
				//grey vertex => a cycle
			else if(graph->vertices[u].mark == GREY) {
				pe->type = BACK;
				Incident_del(&(graph->vertices[u].incident), start);
				//min from back level values
				graph->vertices[start].up = MIN(graph->vertices[start].up,
				                                graph->vertices[u].level);
			}
		}
		else if(pe->type == MULTIPLE) {
			//Orient and classify an incident edge
			if(graph->vertices[u].mark == WHITE) {
				graph->vertices[u].level = graph->vertices[start].level + 1;
				graph->vertices[u].up = graph->vertices[u].level;
				DFS(graph, u);
				//min from other up values
				graph->vertices[start].up = MIN(graph->vertices[start].up, graph->vertices[u].up);
			}
				//grey vertex => a cycle
			else if(graph->vertices[u].mark == GREY) {
				//min from back level values
				graph->vertices[start].up = MIN(graph->vertices[start].up,
				                                graph->vertices[u].level);
			}
		}
	}
	graph->vertices[start].mark = BLACK;
}

void Graph_free(Graph *graph) {
	free(graph->bridges);
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
	int from, to, ed_num;

	fscanf(fi, "%d %d", &(graph.v_num), &ed_num);
	graph.vertices = malloc(graph.v_num * sizeof(Vertex));
	DFS_init(&graph);

	for(int i = 0; i < ed_num; i++) {
		fscanf(fi, "%d %d", &from, &to);
		Incident_push(&(graph.vertices[from - 1].incident), to - 1, i + 1);
		Incident_push(&(graph.vertices[to - 1].incident), from - 1, i + 1);
	}

	for(int i = 0; i < graph.v_num; i++) {
		if(graph.vertices[i].mark == WHITE) {
			graph.vertices[i].level = 0;
			graph.vertices[i].up = 0;
			DFS(&graph, i);
		}
	}

	my_comp q_func = &q_comp;
	qsort((void *) graph.bridges, graph.br_n, sizeof(int), q_func);
	fprintf(fo, "%d\n", graph.br_n);
	for(int i = 0; i < graph.br_n; i++) {
		fprintf(fo, "%d ", graph.bridges[i]);
	}

	Graph_free(&graph);
	fclose(fi);
	fclose(fo);
	return 0;
}
