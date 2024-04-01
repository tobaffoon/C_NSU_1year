#include <stdio.h>
#define LEN 100000
int main() {
    int n, m;
    scanf("%d", &n);
    int a[LEN], a_check[100001]={0};
    int ncount = n;
    for(int i=0; i<n; i++){
        scanf("%d", &a[i]);
        if(a_check[a[i]]) ncount--;
        else a_check[a[i]]=1;
    }
    scanf("%d", &m);
    int tempb;
    for(int i=0; i<m; i++){
        scanf("%d", &tempb);
        if(a_check[tempb]){
            ncount--;
        }
        a_check[tempb]=0;
    }
    printf("%d\n", ncount);
    if(ncount) {
        for (int i = 0; i < 100001; i++) {
            if (a_check[i]) printf("%d ", i);
        }
    }
    return 0;
}
