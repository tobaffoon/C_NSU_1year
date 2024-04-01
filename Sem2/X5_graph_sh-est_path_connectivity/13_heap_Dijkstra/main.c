#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define NIL -1
#define INFINITY (ULLONG_MAX-300001)
#define UNVISITED 0
#define VISITED 1
#define IN_BH 2

typedef struct Request {
	int fst,
			snd;
} Request;

//info about where does the edge go and what weight it has
typedef struct Edge {
	int to,
			in_id;
	unsigned long long weight;
} Edge;

//growing array
typedef struct Incident {
	int n, cap;
	Edge *edges;
} Incident;

typedef struct Vector {
	int n, cap;
	int *arr;
} Vector;

typedef struct Vertex {
	unsigned long long d;
	int pr_e_id;
	char visit;
	int bh_id;
	Incident incident; //Incident numbers
} Vertex;

typedef struct Graph {
	Vertex *vertices;
	int v_num;          //number of vertices
	int e_num;
	int *pathes;         //contains from vertices to restore path
} Graph;

//key -> d from graph
//value -> vertex id
typedef struct BinHeap {
	int *tree;
	int cur_size;
} BinHeap;

//swaps memory contents of valuables
void swap(int *a, int *b) {
	int temp = *a;
	*a = *b;
	*b = temp;
}

//ensures that children are bigger than their parents
void BH_siftup(Graph graph, BinHeap *heap, int idx) {
	if(idx == 0)
		return;
	int dad = (idx - 1) / 2;
	if(graph.vertices[heap->tree[idx]].d < graph.vertices[heap->tree[dad]].d) {
		swap(heap->tree + idx, heap->tree + dad);
		//swap positions in bh
		swap(&(graph.vertices[heap->tree[idx]].bh_id), &(graph.vertices[heap->tree[dad]].bh_id));
		BH_siftup(graph, heap, dad);
	}
}

//ensures that parents are smaller than their children
void BH_siftdown(Graph graph, BinHeap *heap, int idx) {
	int smallest = idx,
			left_child = 2 * idx + 1,
			right_child = 2 * idx + 2;

	//smallest is idx of the smallest of parent and its children
	if(left_child < heap->cur_size &&
	   graph.vertices[heap->tree[left_child]].d < graph.vertices[heap->tree[idx]].d) {
		smallest = left_child;
	}

	if(right_child < heap->cur_size &&
	   graph.vertices[heap->tree[right_child]].d < graph.vertices[heap->tree[idx]].d) {
		if(graph.vertices[heap->tree[smallest]].d > graph.vertices[heap->tree[right_child]].d) {
			smallest = right_child;
		}
	}

	if(smallest != idx) {
		swap(heap->tree + idx, heap->tree + smallest);
		//swap positions in bh
		swap(&(graph.vertices[heap->tree[idx]].bh_id),
		     &(graph.vertices[heap->tree[smallest]].bh_id));
		BH_siftdown(graph, heap, smallest);
	}
}

//adds new_val to our Binary Heap
void BH_add(Graph graph, BinHeap *heap, int new_val) {
	graph.vertices[new_val].visit = IN_BH;
	heap->tree[heap->cur_size] = new_val;
	graph.vertices[new_val].bh_id = heap->cur_size++;
	BH_siftup(graph, heap, heap->cur_size - 1);
}

int BH_ExtractMin(Graph graph, BinHeap *heap) {
	int res = heap->tree[0];
	swap(heap->tree, heap->tree + heap->cur_size - 1);
	//swap positions in bh
	swap(&(graph.vertices[heap->tree[0]].bh_id),
	     &(graph.vertices[heap->tree[heap->cur_size - 1]].bh_id));
	heap->cur_size--;
	BH_siftdown(graph, heap, 0);
	graph.vertices[res].visit = VISITED;
	return res;
}

void Incident_push(Incident *ls, int to, unsigned long long weight, int id) {
	if(ls->cap == 0) {
		ls->cap = 2;
		ls->edges = malloc(sizeof(Edge) * ls->cap);
	}
	if(ls->n == ls->cap) {
		ls->cap *= 2;
		ls->edges = (Edge *) realloc(ls->edges, sizeof(Edge) * ls->cap);
	}
	ls->edges[ls->n].to = to;
	ls->edges[ls->n].weight = weight;
	ls->edges[ls->n++].in_id = id;
}

void Vector_push(Vector *ls, int val) {
	if(ls->cap == 0) {
		ls->cap = 2;
		ls->arr = malloc(sizeof(int) * ls->cap);
	}
	if(ls->n == ls->cap) {
		ls->cap *= 2;
		ls->arr = (int *) realloc(ls->arr, sizeof(int) * ls->cap);
	}
	ls->arr[ls->n++] = val;
}

//relax (u,v) edge, supposing the input is correct + push new value to the priority queue
void Relax(Graph graph, int u, Edge v, BinHeap *heap) {
	//v.d > u.d + w(u,v)
	if(graph.vertices[v.to].d > graph.vertices[u].d + v.weight) {
		graph.vertices[v.to].d = graph.vertices[u].d + v.weight;
		graph.vertices[v.to].pr_e_id = v.in_id;
		//we UPDATED the key - now siftup (because we may have only decreased it)
		if(graph.vertices[v.to].visit == IN_BH) {
			BH_siftup(graph, heap, graph.vertices[v.to].bh_id);
		}
		else if(graph.vertices[v.to].visit == UNVISITED) {
			BH_add(graph, heap, v.to);
		}
	}
}

void Dijkstra_init(Graph graph, int from) {
	for(int i = 0; i < graph.v_num; i++) {
		graph.vertices[i].d = INFINITY;
		graph.vertices[i].pr_e_id = NIL;
		graph.vertices[i].visit = UNVISITED;
	}
	graph.vertices[from].d = 0;
}

void Dijkstra(Graph graph, int from, BinHeap heap) {
	Dijkstra_init(graph, from);
	BH_add(graph, &heap, from);
	int u,      //current vertex
	adj_num;    //number of vertices adjacent to u
	while(heap.cur_size != 0) {
		u = BH_ExtractMin(graph, &heap);
		adj_num = graph.vertices[u].incident.n;
		for(int i = 0; i < adj_num; i++) {
			//relax(u, v) for some adjacent v
			Relax(graph, u, graph.vertices[u].incident.edges[i], &heap);
		}
	}
}

void Print_shortest_path(Graph graph, int from, int to, FILE *out) {
	if(graph.vertices[to].d == INFINITY || graph.vertices[to].pr_e_id == NIL) {
		fprintf(out, "DOOMED\n");
		return;
	}
	fprintf(out, "quarantine  %llu ", graph.vertices[to].d);
	Vector path = {0, 0, 0};
	while(from != to) {
		Vector_push(&path, graph.vertices[to].pr_e_id + 1);
		to = graph.pathes[graph.vertices[to].pr_e_id];
	}
	fprintf(out, "%d ", path.n);
	for(int i = path.n - 1; i >= 0; i--) {
		fprintf(out, " %d", path.arr[i]);
	}
	fprintf(out, "\n");
	free(path.arr);
}

void Graph_free(Graph *graph) {
	for(int i = 0; i < graph->v_num; i++) {
		free(graph->vertices[i].incident.edges);
	}
	free(graph->vertices);
	free(graph->pathes);
}

int main() {
	FILE *fi = fopen("input.txt", "r"),
			*fo = fopen("output.txt", "w");
	Graph graph;
	int path_requests;
	fscanf(fi, "%d %d %d", &(graph.v_num), &(graph.e_num), &path_requests);
	graph.vertices = calloc(graph.v_num, sizeof(Vertex));
	graph.pathes = malloc(graph.e_num * sizeof(int));
	Request *requests = malloc(path_requests * sizeof(Request));

	int from, to;
	unsigned long long weight;
	for(int i = 0; i < path_requests; i++) {
		fscanf(fi, "%d %d", &from, &to);
		requests[i].fst = from;
		requests[i].snd = to;
	}
	for(int i = 0; i < graph.e_num; i++) {
		fscanf(fi, "%d %d %llu", &from, &to, &weight);
		Incident_push(&(graph.vertices[from - 1].incident), to - 1, weight, i);
		graph.pathes[i] = from - 1;
	}
	BinHeap bh;
	bh.tree = malloc(graph.v_num * sizeof(int));
	bh.cur_size = 0;
	for(int i = 0; i < path_requests; i++) {
		Dijkstra(graph, requests[i].fst - 1, bh);
		Print_shortest_path(graph, requests[i].fst - 1, requests[i].snd - 1, fo);
	}
	Graph_free(&graph);
	free(requests);
	free(bh.tree);
	fclose(fi);
	fclose(fo);
	return 0;
}