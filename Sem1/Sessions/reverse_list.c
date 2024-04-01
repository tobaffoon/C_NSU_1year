#include <stdio.h>
typedef struct Node_s{
    int value;
    struct Node_s *next;
} Node;
Node* invert (Node *head){
    Node *t, *new_head = NULL;
    while(head != NULL){
        t=head;
        head = head->next;
        t->next = new_head;
        new_head = t;
    }
    return new_head;
}
int main() {
    printf("Hello, World!\n");
    return 0;
}
