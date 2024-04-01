#include <stdio.h>


//table of remainders - factorials
int fact_mod[1000001];

//calculates remainder of division by module of (number)! - factorial
void fact_mod_fill(int module){
    fact_mod[0] = 1;
    long long result = 1;
    for(int i = 1; i <= 1000000; i++){
            result *= i;                //use result to avoid overflow
            result %= module;
            fact_mod[i] = result;
    }
}

//returns inv(number) by module using Fermat's little theorem
int inv_module_fast_pow(unsigned long long base, int module){
    unsigned long long      result = 1,
    current_power = base % module,
    exponent = module - 2;

    while(exponent != 0){
        if((exponent & 1) != 0) {                               //calculates base^(2^(n+1)) by evaluating base^(2^n)
            result *= current_power;                            //if exponent has k power of, then result has base^(2^k) => multiply by it
            result %= module;
        }
        exponent >>= 1;
        current_power *= current_power;                         //calculate next base^(2^n)
        current_power %= module;
    }

    return result;
}

//returns binomial coefficient "n choose k" mod "module"
int bin_coef(int n, int k, int module){
    if(k < 0 || k > n)
        return 0;

    unsigned long long      result = fact_mod[n],                                              //n!
                            inverse_k = inv_module_fast_pow(fact_mod[k], module),              //1/k!
                            inverse_nk = inv_module_fast_pow(fact_mod[n - k], module);   //1/(n-k)!

    result *= inverse_k;    //result = n!/k!
    result %= module;
    result *= inverse_nk;  //result = n!/(k!(n-k)!)
    result %= module;

    return result;
}


int main() {
    FILE    *fi = fopen("input.txt", "r"),
            *fo = fopen("output.txt", "w");

    int     module = 1000000007,
            tests,
            elements,               //n
            k_comb;                 //k

    fscanf(fi, "%d", &tests);

    fact_mod_fill(module);

    for (int i = 0; i < tests; ++i) {
        fscanf(fi, "%d%d", &elements, &k_comb);

        fprintf_s(fo, "%d\n", bin_coef(elements, k_comb, module));
    }
    fclose(fi);
    fclose(fo);
    return 0;
}
