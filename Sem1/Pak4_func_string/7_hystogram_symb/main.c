#include <stdio.h>
#define LEN 100000
int main() {
    int symbols[95] = {0};
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    char cur;
    while((cur = getchar()) != EOF){
        symbols[cur-32]++;
    }
    for(int i = 0; i<95; i++){
        if(symbols[i]!=0){
            printf("%c ", i+32);
            while(symbols[i]>0){
                printf("#");
                symbols[i]--;
            }
            printf("\n");
        }
    }
    return 0;
}
