#include <stdio.h>
#define MAX_LEN 1000000
void find_word(char* cur){
    while(*cur == '.' || *cur == ',' || *cur == ';' || *cur == ':'){
        cur++;
        //printf("%c\n", *cur);
    }
    if(!(*cur)) return;
    int total=0, upper=0;
    while(*cur <= 'z' && *cur >= 'A'){
        total++;
        if(*cur <= 'Z') upper++;
        cur++;
    }
    cur-=total;
    printf("%d/%d ", upper, total);
    while(total--){
        printf("%c", *cur);
        cur++;
    }
    printf("\n");
    find_word(cur);
}
int main() {
    char str[MAX_LEN];
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    scanf("%s", str);
    find_word(str);
    return 0;
}
