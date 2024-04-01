#include <stdio.h>

int main() {
    freopen("output.txt", "w", stdout);
    freopen("input.txt", "r", stdin);
    int n, t;
    scanf("%d", &n);
    int sum=0;
    for(int i=0; i<n; i++){
        scanf("%d", &t);
        if(t%2==0) sum+=t;
    }
    printf("%d", sum);
    return 0;
}
