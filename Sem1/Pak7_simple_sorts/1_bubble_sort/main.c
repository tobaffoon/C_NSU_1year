#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define LEN 100002
typedef struct Node_s{
    int key;
    char value[8];
} Node;
Node fst_nodes[LEN] = {0, NULL};
void bubble_s(int len, Node *list){
    int border;
    for(int i = 0; i<len-1; i++){
        border = len-i-1;
        for (int j = 0; j < border; j++) {
            if(fst_nodes[j].key > fst_nodes[j+1].key){
                int temp_key = fst_nodes[j].key;
                char temp_value[8];
                strcpy(temp_value, fst_nodes[j].value);
                fst_nodes[j].key=fst_nodes[j+1].key;
                strcpy(fst_nodes[j].value, fst_nodes[j+1].value);
                fst_nodes[j+1].key=temp_key;
                strcpy(fst_nodes[j+1].value, temp_value);
            }
        }
    }
}
int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    int n;
    scanf("%d", &n);
    for(int i=0; i<n; i++){
        scanf("%d%s", &fst_nodes[i].key, fst_nodes[i].value);
    }
    bubble_s(n, fst_nodes);
    for(int i = 0; i<n; i++){
        printf("%d %s\n", fst_nodes[i].key, fst_nodes[i].value);
    }
    return 0;
}
