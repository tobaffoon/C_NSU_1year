#include <stdio.h>

int main() {
    freopen("output.txt", "w", stdout);
    freopen("input.txt", "r", stdin);
    int x,y,z;
    scanf("%d%d%d", &x, &y, &z);
    if(x<=0){
        printf("-1");
    }
    else if(y<=0){
        printf("-2");
    }
    else if(z<=0){
        printf("-3");
    }
    else{
        printf("%d", (2*(x*y+y*z+x*z)));
    }
}
