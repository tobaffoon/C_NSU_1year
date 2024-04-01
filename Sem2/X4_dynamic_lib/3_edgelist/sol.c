#include <stdlib.h>
#include "sol.h"

typedef struct Incident {
    int n,
            cap;
    Edge *arr;
} Incident;

void incident_init(Incident *vec) {
    vec->n = 0;
    vec->cap = 0;
//    vec->arr = malloc(sizeof(Edge) * vec->cap);
}

void incident_push(Incident *vec, Edge value) {
    if (vec->cap == 0) {
        vec->cap = 1;
        vec->arr = malloc(sizeof(Edge) * vec->cap);
    }
    if (vec->n == vec->cap) {
        vec->cap *= 2;
        vec->arr = (Edge *) realloc(vec->arr, sizeof(Edge) * vec->cap);
    }
    vec->arr[vec->n++] = value;
}

Incident *incident_table;

/*

int getVerticesCount(){
    return 6;
}

int readEdge(Edge *oEdge){
    static int edge_num = 0;
    Edge edges[6] = {{0, 2, 178}, {3, 4, 207}, {1, 1, 356}, {2, 0, 101}, {4, 1, 286}, {4, 1, 213}};
    if(edge_num == 6)
        return 0;

    *oEdge = edges[edge_num];
    edge_num++;
    return 1;
}
*/

void init() {
    int verticesCount = getVerticesCount();
    incident_table = malloc(verticesCount * sizeof(Incident));
    for (int i = 0; i < verticesCount; i++) {
        incident_init(&(incident_table[i]));
    }

    Edge buffer;
    int nextEdge = readEdge(&buffer);
    while (nextEdge != 0) {
        incident_push(&(incident_table[buffer.from]), buffer);

        Edge temp = {buffer.to, buffer.from, buffer.weight};

        incident_push(&(incident_table[buffer.to]), temp);
        nextEdge = readEdge(&buffer);
    }
}

int getEdgesCount(int iVertex) {
    return incident_table[iVertex].n;
}

Edge getIncidentEdge(int iVertex, int iIndex) {
    if (incident_table[iVertex].cap == 0)
        exit(666);  //iVertex has no incident edges
    return incident_table[iVertex].arr[iIndex];
}