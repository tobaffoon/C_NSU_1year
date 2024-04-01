#include <stdio.h>

//table of remainders - pascal triangle
int pasctr[2001][2001];

//fills table of remainders - pascal triangle
void pasctriangle_fill_mod(int module){
    for (int i = 0; i <= 2000; i++) {
        pasctr[i][0]=1;
        for (int j = 1; j < i; j++) {
            pasctr[i][j]=(pasctr[i-1][j-1]+pasctr[i-1][j]) % module;
        }
        pasctr[i][i]=1;
    }
}

//returns binomial coefficient "n choose k"
int bin_coef(int n, int k){
    if(k < 0 || k > n)
        return 0;

    else{
        return pasctr[n][k];
    }
}


int main() {
    FILE    *fi = fopen("input.txt", "r"),
            *fo = fopen("output.txt", "w");

    int     module,
            tests,
            elements,       //n
            k_comb;         //k

    fscanf(fi, "%d%d", &module, &tests);

    pasctriangle_fill_mod(module);

    for (int i = 0; i < tests; ++i) {
        fscanf(fi, "%d%d", &elements, &k_comb);

        fprintf_s(fo, "%d\n", bin_coef(elements, k_comb));
    }
    fclose(fi);
    fclose(fo);
    return 0;
}
