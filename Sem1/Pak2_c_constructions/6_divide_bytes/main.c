#include <stdio.h>

int main() {
    int n, sum=0;
    scanf("%d", &n);
    scanf("\n");
    char ch;
    for(int i=1; n>0; i*=2){
        if(i==256){
            printf("%d ", sum);
            sum=0;
            i=1;
        }
        scanf("%c", &ch);
        sum+=(ch-'0')*i;
        n--;
    }
    printf("%d", sum);
    return 0;
}
