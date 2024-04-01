#include <stdio.h>
#include <stdlib.h>
int mabs(int n){
    if(n < 0) return (-1)*n;
    return n;
}
typedef struct res_form{
    int id;
    int val;
} answer;
answer special_bin_search(const int *a, int r, const int num){
    int l = 0;
    int id=0, cur_a, cur_dif, res = mabs(*a-num), res_id=0;
    while(l<=r && res){
        id = (r+l)/2;
        cur_a = *(a+id);
        cur_dif = mabs(cur_a - num);
        if(cur_dif <= res){
            res = cur_dif;
            res_id = id;
        }
        if(cur_a > num){
            r = id - 1;
            continue;
        }
        l = id + 1;
    }
    answer new;
    new.id = res_id;
    new.val = res;
    return new;
}
int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    int q, n, *ar;
    scanf("%d", &n);
    ar = malloc(sizeof(int) * n);
    for(int i = 0; i < n; i++){
        scanf("%d", &ar[i]);
    }
    scanf("%d", &q);
    int cur;
    answer ans;
    for(int i = 0; i < q; i++){
        scanf("%d", &cur);
        ans = special_bin_search(ar, n-1, cur);
        printf("%d %d\n", ans.id, ans.val);
    }
    free(ar);
    return 0;
}
