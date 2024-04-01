#include <stdio.h>
typedef struct LongNum_s {
    int len;
    char arr[500];
} LongNum;
void longsum(LongNum *n1, LongNum *n2){             //always n1>=n2
    char a;
    char more_then_nine=0;
    int i=0;
    while(i<n1->len){
        a = (n1->arr)[i] + (n2->arr)[i];
        if(more_then_nine){
            a++;
            more_then_nine=0;
        }
        if(a>9){
            more_then_nine=1;
            a-=10;
        }
        (n1->arr)[i]=a;
        i++;
    }
    if(more_then_nine){
        (n1->arr)[i]=1;
        n1->len++;
    }
}
void fib(int n, LongNum *prev1, LongNum *prev2){
    if(n<=2) return;
    else{
        LongNum temp = *prev1;
        longsum(prev1, prev2);
        return fib(n-1, prev1, &temp);
    }
}
void long_prnt(LongNum *s){
    for(int i=s->len-1; i>=0; i--){
        printf("%d",(s->arr)[i]);
    }
}
int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    int n;
    scanf("%d", &n);
    LongNum a1 = {1, 1};
    LongNum a2 = {1, 1};
    fib(n, &a1, &a2);
    long_prnt(&a1);
    return 0;
}
