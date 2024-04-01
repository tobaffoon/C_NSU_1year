#include <stdio.h>

int gcd(int a, int b){
    if(b == 0)
        return a;

    return gcd(b, a%b);
}

int main() {
    FILE    *fi = fopen("input.txt", "r"),
            *fo = fopen("output.txt", "w");

    int     tests,
            first_number,
            second_number;

    fscanf(fi, "%d", &tests);

    for (int i = 0; i < tests; ++i) {
        fscanf(fi, "%d%d", &first_number, &second_number);

        fprintf_s(fo, "%d\n", gcd(first_number, second_number));
    }

    fclose(fi);
    fclose(fo);
    return 0;
}
