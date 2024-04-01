#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LENGTH 1000001

typedef char name[8];

typedef struct my_list{
    int cur_size,
        free_size;

    name *names;
} list;

list*   allocate_list      (int num_of_elems);
void    free_list          (list *remove);
void    my_list_realloc    (list *src);
void    add_to_list        (list *dest, name new);
void    fill_list          (FILE *in, list *dest, int num_of_elements);
void    print_list         (FILE *out, list *src);

//initialises list
list* allocate_list(int num_of_elems){
    list *lst = calloc(num_of_elems, sizeof(list));
    for(int i = 0; i < LENGTH; i++){
        lst[i].free_size = 1;
        lst[i].names = NULL;
    }
    return lst;
}

//frees all the allocated strings
/*void free_list(list *remove){
    for(int i = 0; i < LENGTH; i++){
        int current = remove[i].cur_size;
        for(int j = 0; j < current; j++){
            free((remove[i].names) + j);
        }
    }
    free(remove);
}*/

//allocate two times bigger memory section, copy contents there
void my_list_realloc(list *src){
    name *new = calloc(src -> cur_size * 2, sizeof(name));
    memcpy(new, src -> names, sizeof(name) * src -> cur_size);          //copies content of our memory section
    src -> free_size *= 2;
    name *trash = src -> names;
    (src -> names) = new;
    free(trash);
}

//places new element to the names array
void add_to_list(list *dest, name new){
    if(dest -> names == NULL){
        dest -> names = calloc(1, sizeof(name));                //if there is no pointer yet - allocate one. Maybe it would be more effective to allocate them in "allocate_list"
    }
    if(dest -> cur_size >= dest -> free_size){
        my_list_realloc(dest);
    }
    strcpy((char *)((dest -> names) + dest -> cur_size), new);
    dest -> cur_size ++;
}

//adds new elements based on their indexes and contents
void fill_list(FILE *in, list *dest, int num_of_elements){
    for(int i = 0; i < num_of_elements; i++){
        int idx;
        name str;
        fscanf(in, "%d %s", &idx, str);
        add_to_list(dest + idx, str);
    }
}

//traverses the array, printing everything there
void print_list(FILE *out, list *src){
    for(int i = 0; i < LENGTH; i++){
        int current = src[i].cur_size;
        for(int j = 0; j < current; j++){
            fprintf(out, "%d %s\n", i, (char *)((src[i].names) + j));
        }
    }
}

int main() {
    FILE    *fi = fopen("input.txt", "r"),
            *fo = fopen("output.txt", "w");

    list *head = allocate_list(LENGTH);
    int n;
    fscanf(fi, "%d", &n);
    fill_list(fi, head, n);
    print_list(fo, head);
//    free_list(head);
    free(head);
    fclose(fi);
    fclose(fo);
    return 0;
}
