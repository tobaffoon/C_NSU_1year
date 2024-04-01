#include <stdio.h>
#include <stdlib.h>
int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    int n;
    scanf("%d", &n);
    unsigned long long *ar = malloc(sizeof(unsigned long long) * n), count = 0;
    for(int i = 0; i < n; i++) scanf("%llx\n", (ar+i));
    for(int i = 0; i < n; i++){
        unsigned long long cur = ar[i];
        for (int j = i+1; j < n; j++) {
            if(!(cur & ar[j])) count++;
        }
    }
    printf("%lld", count);
    return 0;
}
