#include <stdio.h>
#include <stdlib.h>

enum Visited{
    visited = 0,
    not_visited = 1
};

typedef struct Coord{
    int x,
        y;
} Coord;

typedef struct Queue{
    int first,
            last;
    Coord *arr;
} Queue;

void push_q(Queue *queue, Coord v) {
    queue->arr[queue->last++] = v;
}

Coord pop_q(Queue *queue){
    //queue is empty
    if(queue->first == queue->last){
        Coord res = {-1,-1};
        return res;
    }
    return queue->arr[queue->first++];
}

typedef struct Cell{
    char value;
    int path_length;
    enum Visited visited;       //was it visited (included in any of the components)
} Cell;

typedef struct Labyrinth{
    Cell** layout;          //all the labyrinth NxM
    int width,
        height;
} Labyrinth;

void find_start(const Labyrinth labyrinth, Coord *start){
    for (int i = 0; i < labyrinth.height; i++) {
        for (int j = 0; j < labyrinth.width; j++) {
            if(labyrinth.layout[i][j].value == 'S'){
                start->x = j;
                start->y = i;
                return;
            }
        }
    }
}

//returns 0 if 'F' wasn't found, 1 otherwise
char push_adj(Labyrinth labyrinth, Queue *queue, Coord cell){
    labyrinth.layout[cell.y][cell.x].visited = visited;
    Coord nbr;
    //check all neighbours + do a step of recursion from them
    //move left and check if left cell isn't a wall or a visited cell
    nbr.x = cell.x - 1;
    nbr.y = cell.y;
    if(nbr.x >= 0 && labyrinth.layout[nbr.y][nbr.x].visited == not_visited){
        if(labyrinth.layout[nbr.y][nbr.x].value == '.'){
            labyrinth.layout[nbr.y][nbr.x].visited = visited;
            labyrinth.layout[nbr.y][nbr.x].path_length = labyrinth.layout[cell.y][cell.x].path_length + 1;
            push_q(queue, nbr);
        }
        else if(labyrinth.layout[nbr.y][nbr.x].value == 'F'){
            labyrinth.layout[nbr.y][nbr.x].path_length = labyrinth.layout[cell.y][cell.x].path_length + 1;
            return 1;
        }
    }
    //move up and check if upper cell isn't a wall or a visited cell
    nbr.x = cell.x;
    nbr.y = cell.y - 1;
    if(nbr.y >= 0 && labyrinth.layout[nbr.y][nbr.x].visited == not_visited){
        if(labyrinth.layout[nbr.y][nbr.x].value == '.'){
            labyrinth.layout[nbr.y][nbr.x].visited = visited;
            labyrinth.layout[nbr.y][nbr.x].path_length = labyrinth.layout[cell.y][cell.x].path_length + 1;
            push_q(queue, nbr);
        }
        else if(labyrinth.layout[nbr.y][nbr.x].value == 'F'){
            labyrinth.layout[nbr.y][nbr.x].path_length = labyrinth.layout[cell.y][cell.x].path_length + 1;
            return 1;
        }
    }
    //move right and check if right cell isn't a wall or a visited cell
    nbr.x = cell.x + 1;
    nbr.y = cell.y;
    if(nbr.x < labyrinth.width && labyrinth.layout[nbr.y][nbr.x].visited == not_visited){
        if(labyrinth.layout[nbr.y][nbr.x].value == '.'){
            labyrinth.layout[nbr.y][nbr.x].visited = visited;
            labyrinth.layout[nbr.y][nbr.x].path_length = labyrinth.layout[cell.y][cell.x].path_length + 1;
            push_q(queue, nbr);
        }
        else if(labyrinth.layout[nbr.y][nbr.x].value == 'F'){
            labyrinth.layout[nbr.y][nbr.x].path_length = labyrinth.layout[cell.y][cell.x].path_length + 1;
            return 1;
        }
    }
    //move down and check if bottom cell isn't a wall or a visited cell
    nbr.x = cell.x;
    nbr.y = cell.y + 1;
    if(nbr.y < labyrinth.height && labyrinth.layout[nbr.y][nbr.x].visited == not_visited){
        if(labyrinth.layout[nbr.y][nbr.x].value == '.'){
            labyrinth.layout[nbr.y][nbr.x].visited = visited;
            labyrinth.layout[nbr.y][nbr.x].path_length = labyrinth.layout[cell.y][cell.x].path_length + 1;
            push_q(queue, nbr);
        }
        else if(labyrinth.layout[nbr.y][nbr.x].value == 'F'){
            labyrinth.layout[nbr.y][nbr.x].path_length = labyrinth.layout[cell.y][cell.x].path_length + 1;
            return 1;
        }
    }
    return 0;
}

int BFS_SH_PTH(Labyrinth labyrinth, Coord start){
    Queue queue;
    queue.arr = malloc(labyrinth.width * labyrinth.height * sizeof(Coord));
    queue.first = 0;
    queue.last = 0;

    Coord cur_c = start;
    //while we didn't find a Finish
    while(push_adj(labyrinth, &queue, cur_c) != 1){
        cur_c = pop_q(&queue);
        //if queue is empty
        if(cur_c.x == -1) {
            return -1;
        }
    }

    free(queue.arr);
    return labyrinth.layout[cur_c.y][cur_c.x].path_length;
}

int main() {
    FILE    *fi = fopen("input.txt", "r"),
            *fo = fopen("output.txt", "w");

    Labyrinth labyrinth;
    fscanf(fi, "%d %d", &labyrinth.height, &labyrinth.width);
    fgetc(fi);  //read '\n'
    labyrinth.layout = malloc(labyrinth.height * sizeof(Cell*));                //allocate whole table
    for (int i = 0; i < labyrinth.height; i++) {
        labyrinth.layout[i] = malloc(labyrinth.width * sizeof(Cell));
        for (int j = 0; j < labyrinth.width; j++) {
            labyrinth.layout[i][j].value = fgetc(fi);                   //initialize a cell
            labyrinth.layout[i][j].visited = not_visited;
            labyrinth.layout[i][j].path_length = -1;
        }
        fgetc(fi);  //read '\n'
    }
    Coord start;
    find_start(labyrinth, &start);
    labyrinth.layout[start.y][start.x].path_length = 1;

    fprintf(fo, "%d", BFS_SH_PTH(labyrinth, start));
    fclose(fi);
    fclose(fo);
    return 0;
}