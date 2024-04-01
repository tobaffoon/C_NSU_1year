#include <stdio.h>

int main() {
    //freopen("output.txt", "w", stdout);
    //freopen("input.txt", "r", stdin);
    int a,b;
    scanf("%d%d", &a,&b);
    if(a%b==0){
        printf("%d %d %d 0", a/b, a/b, a/b);
    }
    else if(a>=0){
        printf("%d %d %d %d", a/b, a/b+1, a/b, a%b);
    }
    else{
        printf("%d %d %d ", a/b-1, a/b, a/b, a%b);
        if(a%b){
            printf("%d", a%b+b);
        }
        else printf("%d", a%b);
    }
    return 0;
}
