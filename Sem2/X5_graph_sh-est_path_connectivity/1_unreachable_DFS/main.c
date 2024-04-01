#include <stdio.h>
#include <stdlib.h>

enum Visit{
    not_visited = 0,
    visited = 1
};

typedef struct Cell{
    char value;             //wall or space ('*' or ' ')
    enum Visit visit;       //was it visited (included in any of the components)
} Cell;

typedef struct Labyrinth{
    Cell** layout;          //all the labyrinth NxN
    int size;               //N
} Labyrinth;

//finds and marks all cells reachable from [start_y][start_z] (using recursion)
void DFS(Labyrinth labyrinth, int start_y, int start_x){
    labyrinth.layout[start_y][start_x].visit = visited;
    //check all neighbours + do a step of recursion from them
    //move left and check if left cell isn't a wall or a visited cell
    if(start_x - 1 >= 0 && labyrinth.layout[start_y][start_x - 1].value == ' ' && labyrinth.layout[start_y][start_x - 1].visit == not_visited){
        DFS(labyrinth, start_y, start_x - 1);
    }
    //move down and check if cell below isn't a wall or a visited cell
    if(start_y + 1 < labyrinth.size && labyrinth.layout[start_y + 1][start_x].value == ' ' && labyrinth.layout[start_y + 1][start_x].visit == not_visited){
        DFS(labyrinth, start_y + 1, start_x);
    }
    //move right and check if right cell isn't a wall or a visited cell
    if(start_x + 1 < labyrinth.size && labyrinth.layout[start_y][start_x + 1].value == ' ' && labyrinth.layout[start_y][start_x + 1].visit == not_visited){
        DFS(labyrinth, start_y, start_x + 1);
    }
    //move up and check if upper cell isn't a wall or a visited cell
    if(start_y - 1 >= 0 && labyrinth.layout[start_y - 1][start_x].value == ' ' && labyrinth.layout[start_y - 1][start_x].visit == not_visited){
        DFS(labyrinth, start_y - 1, start_x);
    }
}

//count number of components in a labyrinth
int count_components(Labyrinth labyrinth){
    int components = 0;                                         //number of components
    for (int i = 0; i < labyrinth.size; i++) {
        for (int j = 0; j < labyrinth.size; j++) {
            if(labyrinth.layout[i][j].value == ' ' && labyrinth.layout[i][j].visit == not_visited){    //there is at least 1-cell long component
                DFS(labyrinth, i, j);                           //find and 'mark' all cells reachable from [i][j]
                components++;                                   //that's the whole component
            }
        }
    }
    return components;
}

int main() {
    FILE    *fi = fopen("input.txt", "r"),
            *fo = fopen("output.txt", "w");
    Labyrinth labyrinth;
    fscanf(fi, "%d", &labyrinth.size);
    fgetc(fi);  //read '\n'
    labyrinth.layout = malloc(labyrinth.size * sizeof(Cell*));                //allocate whole table
    for (int i = 0; i < labyrinth.size; i++) {
        labyrinth.layout[i] = malloc(labyrinth.size * sizeof(Cell));            //allocate one row
        for (int j = 0; j < labyrinth.size; j++) {                                  //read a row
            labyrinth.layout[i][j].value = fgetc(fi);                   //initialize a cell
            labyrinth.layout[i][j].visit = not_visited;
        }
        fgetc(fi);  //read '\n'
    }

    //count and print number of components (-1 because one component is reachable - enter)
    fprintf(fo,"%d", count_components(labyrinth) - 1);

    fclose(fo);
    fclose(fi);
    return 0;
}
