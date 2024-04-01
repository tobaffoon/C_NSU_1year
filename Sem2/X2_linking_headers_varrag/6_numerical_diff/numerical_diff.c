#include <stdio.h>

#define DIFFERENTIAL 0.000000001

extern double Function (double x);

int main() {
    FILE    *fi = fopen("input.txt", "r"),
            *fo = fopen("output.txt", "w");

    int nums;
    double  x,
            fdif;

    fscanf(fi, "%d", &nums);
    for (int i = 0; i < nums; i++) {
        fscanf(fi, "%lf", &x);
        if(x + DIFFERENTIAL > 1)
            fdif = (Function(x) - Function(x - DIFFERENTIAL)) / DIFFERENTIAL;
        else if(x - DIFFERENTIAL < 0)
            fdif = (Function(x + DIFFERENTIAL) - Function(x)) / DIFFERENTIAL;
        else
            fdif = (Function(x + DIFFERENTIAL) - Function(x - DIFFERENTIAL)) / (2 * DIFFERENTIAL);
        fprintf_s(fo, "%.15lf\n", fdif);
    }

    fclose(fi);
    fclose(fo);
    return 0;
}
