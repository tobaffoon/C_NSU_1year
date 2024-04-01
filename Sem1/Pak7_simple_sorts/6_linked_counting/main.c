#include <stdio.h>
typedef struct Node_s{
    int idx;
    unsigned int next_idx;
} Node;
int deleteBeforeAndReplacePointer(Node *a, Node **id, int del){
    for(int i = 0; i < del; i++){
        *id = a + (*id)->next_idx;
    }
    int res = (a + (*id)->next_idx)->idx + 1;
    (*id)->next_idx = (a + (*id)->next_idx)->next_idx;
    *id = (a + (*id)->next_idx);
    return res;
}
int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    int n, q;
    scanf("%d%d", &n, &q);
    q-=2;
    Node ar[5000];
    Node *first = ar;
    for(int i = 0; i < n - 1; i++){
        ar[i].idx = i;
        ar[i].next_idx = i+1;
    }
    ar[n-1].idx = n - 1;
    ar[n-1].next_idx = 0;
    while(first->idx != first->next_idx){
        printf("%d\n", deleteBeforeAndReplacePointer(ar, &first, q));
    }
    printf("%d", (first->idx)+1);
    return 0;
}
