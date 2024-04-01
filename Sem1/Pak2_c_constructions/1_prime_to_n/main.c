#include <stdio.h>
int pr(int a){
    for(int i=2; i*i<=a; i++){
        if(a%i==0){
            return 0;
        }
    }
    return 1;
}
int main() {
    int n;
    scanf("%d", &n);
    for(int i=2; i<=n; i++){
        if(pr(i)) printf("%d\n", i);
    }
    return 0;
}
