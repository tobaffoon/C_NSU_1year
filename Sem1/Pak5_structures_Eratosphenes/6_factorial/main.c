#include <stdio.h>
typedef struct LongNum_s {
    int len;
    char arr[3000];
} LongNum;
void longmult(int mult1, LongNum *mult2){
    unsigned int a;
    unsigned int more_then_nine=0;
    int i=0;
    while(i<mult2->len){
        a = (mult2->arr)[i] * mult1;
        if(more_then_nine){
            a+=more_then_nine;
            more_then_nine=0;
        }
        if(a>9){
            more_then_nine=a/10;
            a=a%10;
        }
        (mult2->arr)[i]=a;
        i++;
    }
    while(more_then_nine){
        (mult2->arr)[i]=more_then_nine%10;
        more_then_nine/=10;
        i++;
    }
    mult2->len=i;
}
void fact(int n, LongNum *a){
    while(n>1){
        longmult(n, a);
        n--;
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
    LongNum x = {1, 1};
    fact(n, &x);
    long_prnt(&x);
    return 0;
}
