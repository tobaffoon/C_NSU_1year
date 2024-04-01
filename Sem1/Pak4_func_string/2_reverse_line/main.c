#include <stdio.h>
#include <string.h>
void reverse(char* ptr, int len){
    int rev_idx;
    for(int i = 0; i < len/2; i++){
        rev_idx = len-i-1;                  //может len-i-2
        ptr[i] += ptr[rev_idx];
        ptr[rev_idx] = ptr[i] - ptr[rev_idx];
        ptr[i] = ptr[i] - ptr[rev_idx];
    }
}
int main() {
    int n;
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    scanf("%d", &n);
    //char c;
    //int str_count;
    for(int i = 0; i < n; i++){
        char str[100];
        //str_count = 0;
        scanf("\n");
        /*while(scanf("%c", &c) != EOF && c != '\n'){
            str[str_count] = c;
            str_count++;
        }*/
        scanf("%s", str);
        reverse(str, strlen(str));
        printf("%s\n", str);
    }
    return 0;
}
