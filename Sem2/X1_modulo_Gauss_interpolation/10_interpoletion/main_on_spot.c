#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define INTERVALS 35
#define POWER 6                                                                                     //degree of polynom + 1 (zero degree)

typedef struct Polynome{
    double*  xs,
            ys,
            cs;
} Polynome;

int get_interval(double num){
    int res = floor(num * INTERVALS);
    if(res == INTERVALS)
        res--;

    return res;
}

double init_func(double x, int len, const double* w, const double* a, const double* b){
    double result = 0;
    for (int i = 0; i < len; i++) {
        result += w[i] * cos(a[i] * x + b[i]);
    }
    return result;
}

void add_eqsn(double **first, const double *second){
    for (int i = 0; i < POWER; i++) {
        (*first)[i] += second[i];
    }
}

void mult_arr(double **line, double c){
    for (int i = 0; i < POWER; i++) {
        (*line)[i] *= c;
    }
}

void next_prod(double** eqsn, double x){
    double* prod_x = malloc(sizeof(double) * POWER);

    prod_x[0] = 0;
    for(int i = 1; i < POWER; i++){
        prod_x[i] = (*eqsn)[i-1];
    }

    mult_arr(eqsn, (-1) * x);

    add_eqsn(eqsn, prod_x);

    free(prod_x);
}

double eval_poly(double arg, const double *poly){
    double  result = poly[0],
            cur_pow = arg;

    for (int i = 1; i < POWER; i++) {
        result += cur_pow * poly[i];
        cur_pow *= arg;
    }

    return result;
}

double* create_poly(int cur_interval, int len, const double* w, const double* a, const double* b){
    double  beg = (double)cur_interval / INTERVALS;

    double  *poly = calloc(POWER, sizeof(double)),
            *xs = malloc(sizeof(double) * POWER),
            *prod = calloc(POWER, sizeof(double));

    for (int i = 0; i < POWER; i++) {
//        xs[i] = init_func(tempx, len, w, a, b);
        xs[i] = beg + (double)i / ((POWER - 1) * INTERVALS);                                        //power - 1 to include right boarder, (power * intervals) because length of the interval is 1/intervals
    }                                                                                               //and distance between args is 1/power

    poly[0] = init_func(xs[0], len, w, a, b);
    prod[0] = 1;

    double  *new_term = malloc(sizeof(double) * POWER),
            c,
            cur_y;

    for (int i = 1; i < POWER; i++) {
        next_prod(&prod, xs[i-1]);
        cur_y = init_func(xs[i], len, w, a, b);

        double temp_prod = eval_poly(xs[i], prod);
        c = (cur_y - eval_poly(xs[i], poly)) / temp_prod;              //c = (y_i - P_(i-1)) / (x_i - x_0)...(x_i - x_(i-1))

        memcpy(new_term, prod, sizeof(double) * POWER);
        mult_arr(&new_term, c);

        add_eqsn(&(poly), new_term);
    }

    free(xs);
    free(prod);
    free(new_term);

    return poly;
}

int main() {
    FILE    *fi = fopen("input.txt", "r"),
            *fo = fopen("output.txt", "w");

    int sum_len,
            in_len;

    fscanf(fi, "%d%d", &sum_len, &in_len);

    double *coefsw = malloc(sizeof(double) * sum_len);
    double *coefsa = malloc(sizeof(double) * sum_len);
    double *coefsb = malloc(sizeof(double) * sum_len);

    for (int i = 0; i < sum_len; i++) {
        fscanf(fi, "%lf", coefsw + i);
        fscanf(fi, "%lf", coefsa + i);
        fscanf(fi, "%lf", coefsb + i);
    }

    double **interpolation = calloc(POWER * INTERVALS, sizeof(double*));

    for(int i = 0; i < INTERVALS; i++){
        interpolation[i] = create_poly(i, sum_len, coefsw, coefsa, coefsb);
    }

    double  cur_arg,
            cur_val;

    int cur_gap;
    for (int i = 0; i < in_len; i++) {
        fscanf(fi, "%lf", &cur_arg);
        cur_gap = get_interval(cur_arg);

        cur_val = eval_poly(cur_arg, interpolation[cur_gap]);
        fprintf_s(fo, "%0.25g\n", cur_val);
    }

    fclose(fi);
    fclose(fo);
    return 0;
}
