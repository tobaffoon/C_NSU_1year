#include <stdio.h>

int main() {
    int h,m,s,k;
    scanf("%d %d %d %d", &h,&m,&s,&k);
    s=s+k;
    m=(m+s/60);
    h=(h+m/60);
    printf("%d %d %d", h%24, m%60, s%60);
    return 0;
}
