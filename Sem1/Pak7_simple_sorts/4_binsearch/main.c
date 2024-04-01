#include <stdio.h>
#include <stdlib.h>
/*int special_bin_search(const int *a, int l, int r, const int num){
    if(l==r){
        if(*(a+l) == num) return l;
        return -1;
    }
    int id = (r+l)/2;
    if((int)(*(a+id)) == num){
        while(id!=r && (int)(*(a+id+1)) == num){
            id++;
        }
        return id;
    }
    if((int)(*(a+id)) < num) special_bin_search(a, id+1, r, num);
    else special_bin_search(a, l, id, num);
}*/
int special_bin_search(const int *a, int r, const int num){
    int l = 0;
    int id, cur_a, res=-1;
    while(l<=r){
        id = (r+l)/2;
        cur_a = *(a+id);
        if(cur_a == num){
            l = id + 1;
            res = id;
            continue;
        }
        if(cur_a < num){
            l = id + 1;
            continue;
        }
        r = id - 1;
    }
    return res;
}
int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    int q, n, *ar;
    scanf("%d", &n);
    ar = malloc(sizeof(int) * (n + 1));
    for(int i = 0; i < n; i++){
        scanf("%d", &ar[i]);
    }
    ar[n]=1000000001;
    scanf("%d", &q);
    int prev_res = 0, cur;
    for(int i = 0; i < q; i++){
        scanf("%d", &cur);
        //prev_res = special_bin_search(ar, 0, n-1, cur+prev_res);
        prev_res = special_bin_search(ar, n-1, cur+prev_res);
        printf("%d\n", prev_res);
    }
    free(ar);
    return 0;
}
