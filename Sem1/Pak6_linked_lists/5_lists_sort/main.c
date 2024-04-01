#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define LISTS_QUANTITY 1000001
typedef struct Node_s{
    char value[8];
    struct Node_s *next;
} Node;
void append_to_list(Node **dest, char* new_value){
    Node *new = malloc(sizeof(Node));
    strcpy(new->value, new_value);
    new->next = (*dest)->next;
    (*dest)->next = new;
    *dest = new;                                    //so we always append elements to the end
}
void initialize_node(Node **new){
    *new = malloc(sizeof(Node));
}
int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    int n;
    scanf("%d", &n);
    Node **arr = malloc(sizeof(Node *) * LISTS_QUANTITY);
    for(int i = 0; i < LISTS_QUANTITY; i++){
        Node **cur = arr + i;
        initialize_node(cur);
        (*cur)->next = *cur;                                            //I'm going to make a cycle
        strcpy((*cur)->value, "\0");                             //To know when the cycle is over
    }
    int cur_key;
    char *cur_val = malloc(sizeof(char) * 8);
    for(int i = 0; i < n; i++) {
        scanf("%d", &cur_key);
        scanf("%s", cur_val);
        append_to_list(arr + cur_key, cur_val);
    }
    free(cur_val);
    for(int i = 0; i < LISTS_QUANTITY; i++) {
        Node *to_print = arr[i];
        if(to_print != to_print->next){
            to_print = to_print->next->next;                           //now to_print is pointing to the first element (cycle)
            do {
                printf("%d %s\n", i, to_print->value);
                to_print = to_print->next;
            }while(strcmp(to_print->value, "\0"));
        }
    }
    free(arr);
    return 0;
}
