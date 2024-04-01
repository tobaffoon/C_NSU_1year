#include <stdio.h>
#include <stdlib.h>

#define NOTVISITED 0
#define VISITED 1
#define UNREACHABLE -1
#define INFINITY INT_MAX

#define MIN(A,B) ((A)<(B)?(A):(B))
#define INV(A) (A^1)

typedef struct Edge{
	int from, to;
	int cap;
	int flow;
} Edge;

typedef struct Incident {
	int n, top;
	int *e_idx;
} Incident;

typedef struct Vertex{
	Incident incident;
	char visit;
	int BFS_depth;
	int BFS_pr_e;
} Vertex;

typedef struct Graph{
	Vertex *vertices;
	int v_num;
	Edge *edges;
	int e_num;
} Graph;

typedef struct Queue{
	int first,
			last,
			*arr;
} Queue;

void push_q(Queue *queue, int v) {
	queue->arr[queue->last++] = v;
}

//push all incident vertices of v and mark them in graph
void push_inc(Graph *graph, Queue *queue, int from){
	int adj_num = graph->vertices[from].incident.n;
	int *inc = graph->vertices[from].incident.e_idx;
	Edge cur_e;
	for (int i = 0; i < adj_num; i++) {
		cur_e = graph->edges[inc[i]];
		if(graph->vertices[cur_e.to].visit == NOTVISITED && cur_e.cap - cur_e.flow > 0) {
			push_q(queue, cur_e.to);
			graph->vertices[cur_e.to].BFS_pr_e = inc[i];
			graph->vertices[cur_e.to].visit = VISITED;
			graph->vertices[cur_e.to].BFS_depth = graph->vertices[from].BFS_depth + 1;
		}
	}
}

int pop_q(Queue *queue){
	return queue->arr[queue->first++];
}

void BFS_init(Graph *graph, Queue *queue, int start){
	queue->first = 0;
	queue->last = 0;
	for(int i = 0; i < graph->v_num; i++) {
		graph->vertices[i].BFS_depth = UNREACHABLE;
		graph->vertices[i].visit = NOTVISITED;
	}
	graph->vertices[start].BFS_depth = 0;
}

void BFS_sh_pth(Graph *graph, Queue queue, int start){
	BFS_init(graph, &queue, start);
	graph->vertices[start].visit = VISITED;
	push_inc(graph, &queue, start);
	int cur_id = pop_q(&queue);

	//while queue is not empty
	while(queue.first <= queue.last){
		push_inc(graph, &queue, cur_id);   //push and mark incident vertices
		cur_id = pop_q(&queue);
	}

}

void Incident_push(Graph graph, int from, int to, int cap, int id) {
	graph.edges[id].to = to;
	graph.edges[id].from = from;
	graph.edges[id].cap = cap;
	graph.edges[id].flow = 0;
	Incident *ls = &(graph.vertices[from].incident);
	if(ls->top == 0){
		ls -> top = 2;
		ls->e_idx = malloc(ls->top * sizeof(int));
	}
	else if(ls->n==ls->top) {
		ls->top *= 2;
		ls->e_idx = (int *) realloc(ls->e_idx, sizeof(int) * ls->top);
	}
	ls->e_idx[ls->n++] = id;
}

long long Max_flow(Graph graph, int s, int t){
	Queue queue;
	queue.arr = calloc(graph.v_num, sizeof(int));
	//evaluate shortest path to t
	BFS_sh_pth(&graph, queue, s);
	while(graph.vertices[t].BFS_depth != UNREACHABLE) {
		int cp = INFINITY,
				cur_v = t;
		while(cur_v != s) {
			//capacity of an edge from which current vertex went
			cp = MIN(cp, graph.edges[graph.vertices[cur_v].BFS_pr_e].cap - graph.edges[graph.vertices[cur_v].BFS_pr_e].flow);
			cur_v = graph.edges[graph.vertices[cur_v].BFS_pr_e].from;
		}

		cur_v = t;
		while(cur_v != s){
			graph.edges[graph.vertices[cur_v].BFS_pr_e].flow += cp;
			graph.edges[INV(graph.vertices[cur_v].BFS_pr_e)].flow -= cp;
			cur_v = graph.edges[graph.vertices[cur_v].BFS_pr_e].from;
		}
		BFS_sh_pth(&graph, queue, s);
	}
	int adj_num = graph.vertices[s].incident.n;
	long long res = 0;
	//evaluate flow leaving from the source
	for(int i = 0; i < adj_num; i++) {
		res += graph.edges[graph.vertices[s].incident.e_idx[i]].flow;
	}
	free(queue.arr);
	return res;
}

void Graph_free(Graph *graph) {
	for(int i = 0; i < graph->v_num; i++) {
		if(graph->vertices[i].incident.top != 0) {
			free(graph->vertices[i].incident.e_idx);
		}
	}
	free(graph->vertices);
	free(graph->edges);
}

int main(){
	FILE *fi = fopen("input.txt", "r"),
			*fo = fopen("output.txt", "w");
	Graph graph;    //first vertex = s, next = students, next = tasks, last = t
	int students, tasks, mapping;
	fscanf(fi, "%d %d %d", &students, &tasks, &mapping);
	graph.v_num = students + tasks + 2;
	graph.vertices = calloc(graph.v_num, sizeof(Vertex));
	graph.edges = malloc((mapping + students + tasks) * 2 * sizeof(Edge));

	graph.e_num = students;
	//add edges between s and students
	for(int i = 0; i < students; i++) {
		Incident_push(graph, i + 1, 0, 1, 2 * i);
		Incident_push(graph, 0, i + 1, 1, 2 * i + 1);
	}
	//add main edges
	graph.e_num += mapping;
	int from, to;
	for(int i = students; i < graph.e_num; i++) {
		fscanf(fi, "%d %d", &from, &to);
		to += students;
		Incident_push(graph, from, to, 1, 2 * i);
		Incident_push(graph, to, from, 0, 2 * i + 1);
	}
	//add edges between between tasks and t
	graph.e_num += tasks;
	for(int i = students + mapping; i < graph.e_num; i++) {
		Incident_push(graph, i + 1 - mapping, graph.v_num-1, 1, 2 * i);
		Incident_push(graph, graph.v_num-1, i + 1 - mapping, 1, 2 * i + 1);
	}

	long long max_flow = Max_flow(graph, 0, graph.v_num-1);
	fprintf(fo, "%lld\n", max_flow);
	for(int i = 1; i <= students; i++) {
		for(int j = 0; j < graph.vertices[i].incident.n; j++) {
			if(graph.edges[graph.vertices[i].incident.e_idx[j]].flow == 1){
				fprintf(fo, "%d %d\n", i, graph.edges[graph.vertices[i].incident.e_idx[j]].to - students);
				break;
			}
		}
	}
	Graph_free(&graph);
	fclose(fi);
	fclose(fo);
	return 0;
}