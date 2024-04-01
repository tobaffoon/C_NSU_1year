#include <stdio.h>
#include <stdlib.h>
typedef struct Node_s{
    double value;
    struct Node_s *next;
} Node;
int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    int n, f, cur_f;
    scanf("%d%d",&n,&f);
    Node *arr = malloc(sizeof(Node)*n);
    Node *cur = arr;
    for(int i = 0; i<n; i++){
        scanf("%lf %d", &cur->value, &cur_f);
        if(cur_f==-1) cur->next=NULL;
        else cur->next=arr+cur_f;
        cur++;
    }
    for(cur = arr + f; cur!=NULL; cur=cur->next){
        printf("%0.3f\n", cur->value);
    }
    /*  3 1
        2.718 2
        1.111 0
        5.0 -1

        1.111
        2.718
        5.0
     */
    /*Node* idToNode[1000010];
    int idcnt;
    scanf(..., &id, &value);
    Node *ptr = idToNode[id];
    Node *new = insertAfter(ptr, value);
    idToNode[idcnt++] = new;
    printf(...);*/
    free(arr);
    return 0;
}
