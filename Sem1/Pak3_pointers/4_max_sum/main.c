#include <stdio.h>
#define LEN 5000
int main() {
    int n;
    scanf("%d", &n);
    int a[LEN];
    for(int i=0; i<n; i++){
        scanf("%d", &a[i]);
    }
    int sum=0, L, R;
    int summax=a[0], Lmax, Rmax;
    for(L=0; L<n; L++){
        sum=0;
        for(R=L; R<n; R++){
            sum+=a[R];
            if(sum>summax){
                summax=sum;
                Lmax=L;
                Rmax=R;
            }
        }
    }
    printf("%d %d %d", Lmax, Rmax, summax);
    return 0;
}
