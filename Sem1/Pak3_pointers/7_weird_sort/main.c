#include <stdio.h>
#define LEN 10000
int main() {
    int n;
    scanf("%d", &n);
    int ar[LEN];
    for(int i = 0; i<n; i++){
        scanf("%d", &ar[i]);
    }
    int counter[100]={0};
    int l, r;
    for(int i=1; i<=199901; i+=100){        //можно посчитать min,max и не идти по всем 200000 числам, а только [min,max]
        l=i-100001;
        r=l+99;
        for(int k=0; k<n; k++){
            if(ar[k]<=r && ar[k]>=l){
                counter[ar[k]-l]++;
                //ar[k]=0;
            }
        }
        for(int k=0; k<100; k++){
            while(counter[k]>0){            //здесь можно ввести счётчик, чтобы по выводу занесённых чисел цикл кончался быстрее
                printf("%d ", (k+l));
                counter[k]--;
            }
        }
    }
    for(int i=0;i<n;i++){
        if(ar[i]==100000) printf("100000");
    }
    return 0;
}
