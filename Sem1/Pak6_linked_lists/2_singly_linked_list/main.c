#include <stdio.h>
#include <string.h>
#define LEN 200000
int elemcnt=0, idx_first;
typedef struct Node_s{
    char word[8];
    int next;
} Node;
int insertAfter(Node *src, int after_idx, char* value){
    strcpy((src+elemcnt)->word, value);
    if(after_idx == -1){
        (src+elemcnt)->next = idx_first;
        idx_first = elemcnt;
    }
    else{
        (src + elemcnt)->next = (src + after_idx)->next;
        (src + after_idx)->next = elemcnt;
    }
    return (elemcnt++);
}
char *deleteAfter(Node *src, int after_idx){
    char* return_value;
    if(after_idx == -1){
        return_value = (src + idx_first)->word;
        idx_first = (src + idx_first)->next;
    }
    else {
        return_value = (char *) &(src + (src + after_idx)->next)->word;
        (src + after_idx)->next = (src + (src + after_idx)->next)->next;
    }
    return return_value;
}
int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    Node text[LEN];
    int t;
    scanf("%d", &t);
    int number_of_operations, cur_operation, operation_index;
    char operation_value[8];
    for (int i = 0; i < t; i++) {
        scanf("%d%d%d", &elemcnt, &idx_first, &number_of_operations);
        for (int j = 0; j < elemcnt; j++) {
            scanf("%s %d", text[j].word, &text[j].next);
        }
        for(int j = 0; j<number_of_operations; j++){
            scanf("%d", &cur_operation);
            if(cur_operation){
                scanf("%d", &operation_index);
                printf("%s\n", deleteAfter(text, operation_index));
            }
            else{
                scanf("%d%s", &operation_index, operation_value);
                printf("%d\n", insertAfter(text, operation_index, operation_value));
            }
        }
        printf("===\n");
        /*for(int j = idx_first; j!=-1; j=text[j].next){
            text[j].next=-1;
            printf("%s\n", text[j].word);
        }*/
        while(idx_first!=-1){
            number_of_operations=idx_first;
            printf("%s\n", text[idx_first].word);
            idx_first=text[idx_first].next;
            text[number_of_operations].next=-1;
        }
        printf("===\n");
    }
    return 0;
}
