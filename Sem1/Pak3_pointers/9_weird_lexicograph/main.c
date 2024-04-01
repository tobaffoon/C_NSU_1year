#include <stdio.h>
#define LEN 26
int main() {
    int n;
    scanf("%d", &n);
    char car[LEN];
    for(int i = 0;i < n; i++){
        scanf(" \n");
        scanf("%c", &car[i]);
    }
    int curr= n - 2, comp_idx=-1;
    while(curr >= 0){
        for(int i = n - 1; i > curr; i--){
            if(car[curr] < car[i]){
                car[curr] += car[i];
                car[i] = car[curr] - car[i];
                car[curr] = car[curr] - car[i];
                comp_idx= curr + 1;
                curr = 0;
                break;
            }
        }
        curr--;                                                     //3 b c a
    }
    if(comp_idx == -1){
        for(int i = 0; i < n; i++){
            printf("%c ", car[i]);
        }
    }
    else {
        for (int i = 0; i < comp_idx; i++) {
            printf("%c ", car[i]);
        }
        int n1_flag = 1;
        for (int i = n - 2; i >= comp_idx; i--) {
            if (n1_flag && car[n - 1] <= car[i]) {
                n1_flag = 0;
                printf("%c ", car[n - 1]);
            }
            printf("%c ", car[i]);
        }
        if (n1_flag) printf("%c ", car[n - 1]);
    }
    return 0;
}
