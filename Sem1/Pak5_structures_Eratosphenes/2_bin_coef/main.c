#include <stdio.h>
double binCo[1001][1001];
void fill_binCo(double (*ar)[1001]){
    for(int i=0; i<=1000; i++){
        ar[i][0]=1;                         //^ n (from what), -> k (how many)
        ar[i][i]=1;
    }
    for(int i=2; i<=1000; i++){
        for(int j=1; j<i; j++){
            ar[i][j]=ar[i-1][j]+ar[i-1][j-1];
        }
    }
}
int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    int m;
    fill_binCo(binCo);
    scanf("%d", &m);
    int n,k;
    for(int i=0; i<m; i++){
        scanf("%d %d", &n,&k);
        printf("%0.10g\n", binCo[n][k]);
    }
    return 0;
}
