#include <stdio.h>
#define LEN 100000
int main() {
    int n;
    scanf("%d", &n);
    int b[LEN];
    for(int i=0; i<n; i++){
        scanf("%d", &b[i]);
    }
    int sumk;
    for(int k=1; k<=n; k++){
        sumk=0;
        for(int j=1; j<=n/k; j++){
            sumk+=b[j*k-1];
        }
        printf("%d\n", sumk);
    }
    return 0;
}
