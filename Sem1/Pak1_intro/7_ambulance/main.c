#include <stdio.h>

int main() {
    //freopen("output.txt", "w", stdout);
    //freopen("input.txt", "r", stdin);
    /*int n, m, p, k, l;
    scanf("%d %d %d %d %d", &n, &m, &p, &k , &l);
    int s = m/((p-1)*l+k-1);                                         //кол-во квартир на этаже
    if(m%s==0) s-=1;
    int pod= (n%(s*l)==0)?(n/(s*l)):(n/(s*l)+1);
    int et = (n%s==0)?((n-s*l*(pod-1))/s):((n-s*l*(pod-1))/s+1);     //Этаж
    printf("%d %d", pod, et);
    return 0;*/
    int n, m, p, k, l;
    scanf("%d %d %d %d %d", &n, &m, &p, &k , &l);
    int s = (m-1)/((p-1)*l+k-1);
    int pod= (n-1)/(s*l)+1;
    int et = (n-s*l*(pod-1)-1)/s+1;     //Этаж
    printf("%d %d", pod, et);
    return 0;
}
