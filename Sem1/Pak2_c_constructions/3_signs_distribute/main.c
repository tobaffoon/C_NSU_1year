#include <stdio.h>

int main() {
    double pos=0, neg=0, nul;
    int n;
    scanf("%d", &n);
    int t;
    for(int i=0; i<n; i++){
        scanf("%d", &t);
        if(t>0) pos++;
        else if(t<0) neg++;
    }
    nul=n-pos-neg;
    printf("%lf %lf %lf", (neg/n), nul/n, pos/n);
    return 0;
}
