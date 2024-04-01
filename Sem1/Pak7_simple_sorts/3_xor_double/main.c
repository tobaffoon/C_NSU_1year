#include <stdio.h>

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    int n;
    double numerator, denomenator;
    long long *special_double = (long long *)(&numerator);
    long long xmask;
    scanf("%d", &n);
    for(int i = 0; i < n; i++){
        scanf("%lf/%lf xor %llx", &numerator, &denomenator, &xmask);
        numerator /= denomenator;
        xmask ^= *((long long*)&numerator);
        /*long long xormask;
        for(int j = 0; j < 64; j++){
            xormask = xmask & 1LL;
            xmask = xmask >> 1;
            *special_double ^= (xormask << j);
        }
        printf("%0.15g\n", *((double *)special_double));*/
        printf("%0.15g\n", *((double*)&xmask));
    }
    return 0;
}
