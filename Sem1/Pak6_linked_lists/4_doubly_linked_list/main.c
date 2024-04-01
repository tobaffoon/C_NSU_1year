#include <stdio.h>
#include <stdlib.h>
#define LEN 200001
typedef struct Node_s{
    int val;
    int prev;
    int next;
} Node;
int insertAfter(Node *src, int after_idx, int value, int *elemcnt){
    (src + *elemcnt)->val = value;
    (src + *elemcnt)->next = (src + after_idx)->next;                   //place elem
    (src + *elemcnt)->prev = after_idx;
    (src + (src + after_idx)->next)->prev = *elemcnt;                   //readdress surrounding nodes
    (src + after_idx)->next = *elemcnt;
    return (*elemcnt)++;
}
int insertBefore(Node *src, int before_idx, int value, int *elemcnt){
    (src + *elemcnt)->val = value;
    (src + *elemcnt)->next = before_idx;                                 //place elem
    (src + *elemcnt)->prev = (src + before_idx)->prev;
    (src + (src + before_idx)->prev)->next = *elemcnt;                   //readdress surrounding nodes
    (src + before_idx)->prev = *elemcnt;
    return (*elemcnt)++;
}
int deleteElem(Node *src, int del_idx){
    int return_value = (src + del_idx)->val;
    (src + (src + del_idx)->prev)->next = (src + del_idx)->next;
    (src + (src + del_idx)->next)->prev = (src + del_idx)->prev;
    return return_value;
}
int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    int t;
    Node *list=malloc(sizeof(Node)*LEN);
    list++;
    scanf("%d", &t);
    int number_of_operations, cur_operation, operation_index, elemcount=0;
    int operation_value;
    for (int i = 0; i < t; i++){
        scanf("%d%d%d%d", &elemcount, &list[-1].next, &list[-1].prev, &number_of_operations);
        for (int j = 0; j < elemcount; j++) {
            scanf("%d %d %d", &list[j].val, &list[j].next, &list[j].prev);
        }
        for(int j = 0; j<number_of_operations; j++){
            scanf("%d", &cur_operation);
            if(cur_operation){
                scanf("%d%d", &operation_index, &operation_value);
                if(cur_operation==1){
                    printf("%d\n", insertAfter(list, operation_index, operation_value, &elemcount));
                    continue;
                }
                printf("%d\n", insertBefore(list, operation_index, operation_value, &elemcount));
                continue;
            }
            scanf("%d", &operation_index);
            printf("%d\n", deleteElem(list, operation_index));
        }
        printf("===\n");
        for(int j = list[-1].next; j!=-1; j=list[j].next) printf("%d\n", list[j].val);
        printf("===\n");
        fflush(stdout);
    }
    return 0;
}
