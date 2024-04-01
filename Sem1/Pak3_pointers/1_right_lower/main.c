#include <stdio.h>
#define LEN 100
int main() {
    int n;
    scanf("%d", &n);
    int b[LEN];
    for(int i=0; i<n; i++){
        scanf("%d", &b[i]);
    }
    int ch;
    for(int i=0; i<n; i++){
        ch=0;
        for(int j=i+1; j<n; j++){
            if (b[j]<b[i]) ch++;
        }
        printf("%d ", ch);
    }
    return 0;
}
