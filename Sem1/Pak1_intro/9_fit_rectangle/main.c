#include <stdio.h>

int main() {
    long long n, ans=0, k;
    //176 ms
    scanf("%lld", &n);
    for(int i=1; i*i*i<=n;i++){
        for(int j=i; j*j<=n; j++){
            k=n/(i*j);
            if(k>=j) ans+=k-(j-1);
        }
    }
    printf("%lld", ans);
    return 0;
}
