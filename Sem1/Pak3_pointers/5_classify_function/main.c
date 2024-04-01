#include <stdio.h>
#define N_LEN 300
/*Для заданного отношения 𝑅 требуется определить:
1. Является ли 𝑅 функцией: ∀𝑥 ∈ 𝑃 : (𝑥, 𝑢) ∈ 𝑅 и (𝑥, 𝑣) ∈ 𝑅 ⇒ 𝑢 = 𝑣 — отсутствует
многозначность.
2. Является ли 𝑅 всюду определённой функцией: 𝑅 является функцией и ∀𝑥 ∈ 𝑁 ∃ 𝑦 |
(𝑥, 𝑦) ∈ 𝑅 — значение определено на всём множестве 𝑃 .
3. Является ли 𝑅 инъективной функцией: 𝑅 является функцией и (𝑥, 𝑢) ∈ 𝑅 и (𝑦, 𝑢) ∈ 𝑅
⇒ 𝑥 = 𝑦.
4. Является ли 𝑅 сюръективной функцией: 𝑅 является функцией и ∀𝑢 ∈ 𝑁 ∃ 𝑥 | (𝑥, 𝑢) ∈ 𝑅.
5. Является ли 𝑅 биективной функцией: функция 𝑅 и инъективна, и сюръективна.*/
int main() {
    int n,m;
    scanf("%d%d", &n,&m);
    int a[N_LEN], b[N_LEN], a_check[300]={0}, b_check[300]={0};
    int flag_iniekt=1, flag_dom=1, flag_suriekt=1;
    for(int i=0; i<m; i++){
        scanf("%d %d", &a[i], &b[i]);
        if(a_check[a[i]-1]){
            printf("0");
            return 0;
        }
        if(b_check[b[i]-1]) flag_iniekt=0;
        a_check[a[i]-1]++;
        b_check[b[i]-1]++;
    }
    printf("1 ");
    for(int i=0; i<n; i++){
        if(a_check[i]==0) flag_dom=0;
        if(b_check[i]==0) flag_suriekt=0;
    }
    if(flag_dom) printf("2 ");
    if(flag_iniekt) printf("3 ");
    if(flag_suriekt){
        printf("4 ");
        if(flag_iniekt && flag_dom) printf("5");
    }
    return 0;
}
