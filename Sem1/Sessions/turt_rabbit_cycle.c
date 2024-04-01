#include <stdio.h>
typedef struct Node_s{
    int value;
    struct Node_s *next;
} Node;
Node *is_cycle(Node *list){
    Node *slow=list, *fast=list->next;
    while(fast!=NULL && fast->next!=NULL){
        if(fast==slow){
            return list;
        }
        fast=fast->next->next;
        slow=slow->next;
    }
    return NULL;
}
int main() {
    printf("Hello, World!\n");
    return 0;
}
