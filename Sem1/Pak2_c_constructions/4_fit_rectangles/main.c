#include <stdio.h>
int min(int a, int b){
    if(a<b) return a;
    return b;
}
int max(int a, int b){
    if(a>b) return a;
    return b;
}
int main() {
    int a1, a2, b1, b2, c1, c2;
    scanf("%d %d %d %d %d %d", &a1, &a2, &b1, &b2, &c1, &c2);
    if((a1 * a2) < (b1 * b2) + (c1 * c2) || max(max(b1,b2),max(c1,c2)) > max(a1,a2)){
        printf("NO");
    }
    else{
        int st1=b1+c1, st2=max(b2,c2);
        if(max(st1,st2) <= max(a1,a2) && min(st1, st2) <= min(a1,a2)){
            printf("YES");
            return 0;
        }
        st1=b1+c2;
        st2=max(b2,c1);
        if(max(st1,st2) <= max(a1,a2) && min(st1, st2) <= min(a1,a2)){
            printf("YES");
            return 0;
        }
        st1=b2+c1;
        st2=max(b1,c2);
        if(max(st1,st2) <= max(a1,a2) && min(st1, st2) <= min(a1,a2)){
            printf("YES");
            return 0;
        }
        st1=b2+c2;
        st2=max(b1,c1);
        if(max(st1,st2) <= max(a1,a2) && min(st1, st2) <= min(a1,a2)){
            printf("YES");
            return 0;
        }
        else printf("NO");
    }
    return 0;
}
