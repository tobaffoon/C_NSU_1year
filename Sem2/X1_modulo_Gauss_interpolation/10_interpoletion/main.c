#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define INTERVALS 50
#define POWER 8                                                                                     //degree of polynom + 1 (zero degree)

typedef struct Poly {
    double *xs,
            *ys,
            *cs;
} Poly;

typedef struct Eval_res {
    double value,
            newprod;
} Eval_res;

double init_func(double x, int len, const double *w, const double *a, const double *b) {
    double result = 0;
    for (int i = 0; i < len; i++) {
        result += w[i] * cos(a[i] * x + b[i]);
    }
    return result;
}

int get_interval(double num) {
    int res = floor(num * INTERVALS);
    if (res == INTERVALS)
        res--;

    return res;
}

Eval_res eval_poly(Poly poly, int n, double x) {
    Eval_res res = {0, 1};

    for (int i = 0; i <= n; i++) {
        res.value += poly.cs[i] * res.newprod;
        res.newprod *= (x - poly.xs[i]);
    }

    return res;
}

Poly create_poly(int cur_interval, int len, const double *w, const double *a, const double *b) {
    Poly poly;
    poly.xs = malloc(POWER * sizeof(double));
    poly.ys = malloc(POWER * sizeof(double));
    poly.cs = malloc(POWER * sizeof(double));

    double beg = (double) cur_interval;
    beg /= INTERVALS;

    for (int i = 0; i < POWER; i++) {
        poly.xs[i] = beg + ((double) i) / ((POWER - 1) * INTERVALS);
        poly.ys[i] = init_func(poly.xs[i], len, w, a, b);
    }

    poly.cs[0] = poly.ys[0];

    for (int i = 1; i < POWER; i++) {
        Eval_res pr_poly = eval_poly(poly, i - 1, poly.xs[i]);

        poly.cs[i] = (poly.ys[i] - pr_poly.value) / pr_poly.newprod;
    }

    return poly;
}

int main() {
    FILE *fi = fopen("input.txt", "r"),
            *fo = fopen("output.txt", "w");

    int sum_len,
            arg_num;

    fscanf(fi, "%d%d", &sum_len, &arg_num);

    double *ws = malloc(sizeof(double) * sum_len);
    double *as = malloc(sizeof(double) * sum_len);
    double *bs = malloc(sizeof(double) * sum_len);

    for (int i = 0; i < sum_len; i++) {
        fscanf(fi, "%lf", ws + i);
        fscanf(fi, "%lf", as + i);
        fscanf(fi, "%lf", bs + i);
    }

    Poly *interpolation = calloc(INTERVALS, sizeof(Poly));

    for (int i = 0; i < INTERVALS; i++) {
        interpolation[i] = create_poly(i, sum_len, ws, as, bs);
    }

    double arg;

    int gap;

    for (int i = 0; i < arg_num; i++) {
        fscanf(fi, "%lf", &arg);
        gap = get_interval(arg);

        Eval_res temp_res = eval_poly(interpolation[gap], POWER - 1, arg);
        fprintf_s(fo, "%.17lf\n", temp_res.value);
    }

    fclose(fi);
    fclose(fo);
    return 0;
}