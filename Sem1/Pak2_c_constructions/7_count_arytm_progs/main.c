#include <stdio.h>

int main() {
    int l,r,k;
    scanf("%d%d%d", &l,&r,&k);
    r -= l;
    int sum=0;
    for(r; r + 1 >= k; r--){
        sum+=r/(k - 1) - r/k;
    }
    printf("%d", sum);
    return 0;
}
