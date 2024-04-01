#include <stdio.h>

int main() {
    //freopen("output.txt", "w", stdout);
   // freopen("input.txt", "r", stdin);
    int n,x;
    scanf("%d", &n);
    int max=-10001, min=10001, imax, imin;
    for(int i=0; i<n; i++){
        scanf("%d", &x);
        if(x>max){
            max=x;
            imax=i+1;
        }
        if(x<min){
            min=x;
            imin=i+1;
        }
    }
    printf("%d %d %d %d %d", min, imin, max, imax);
    return 0;
}
