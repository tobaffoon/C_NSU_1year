#include <stdio.h>
char prime_set[15000001];
void fill_prime_set(char *pr_ptr, int n){
    pr_ptr[0]=1;
    pr_ptr[1]=1;
    for(int i = 2; i <= n/2; i++){
        if(!pr_ptr[i]){
            for(int j=2*i; j <= n; j+=i){
                pr_ptr[j]=1;
            }
        }
    }
}
int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    int N;
    scanf("%d", &N);
    fill_prime_set(prime_set, N);
    int Q;
    scanf("%d", &Q);
    int cur;
    for(int i=0; i<Q; i++){
        scanf("%d", &cur);
        printf("%d ", cur);
        if(!prime_set[cur]) printf("prime\n");
        else printf("not\n");
    }

    return 0;
}
