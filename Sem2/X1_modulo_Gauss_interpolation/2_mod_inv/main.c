#include <stdio.h>

//calculates 'base' in the power 'exponent' in modulo 'module'
unsigned int fast_pow(unsigned int base, unsigned int module){
    unsigned long long      result = 1,                     //current value
                            current_power = base % module,  //base raised to current power of two
                            exponent = module - 2;

    while(exponent != 0){               //we set bits of exponent zero one by one and when it becomes zero, we halt
        if((exponent & 1) != 0) {    //if mask (= 2^n, where n is the number of current iteration) is present in decomposition to powers of two of exponent
            result *= current_power;    //we include base^(2^n) in the result
            result %= module;
        }
        exponent >>= 1;              //now we don't need this bit
        current_power *= current_power; //next power = (current power) ^ 2
        current_power %= module;
    }

    return result;
}

int main() {
    FILE    *fi = fopen("input.txt", "r"),
            *fo = fopen("output.txt", "w");

    int quantity,
        modulo,
        current_number;

    fscanf(fi, "%d %d", &quantity, &modulo);

    for (int i = 0; i < quantity; i++) {
        fscanf(fi, "%d", &current_number);
        if(current_number == 0)
            fprintf_s(fo, "-1");

        else
            fprintf_s(fo, "%d", fast_pow(current_number, modulo));

        fprintf_s(fo, "\n");
    }

    fclose(fi);
    fclose(fo);
    return 0;
}
