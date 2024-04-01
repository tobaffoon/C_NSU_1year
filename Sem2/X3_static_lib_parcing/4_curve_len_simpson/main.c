#include <stdio.h>
#include <math.h>

#define SCANPOLY(poly) (fscanf(fi, "%lf%lf%lf%lf", (&((poly).c0)), (&((poly).c1)), (&((poly).c2)), (&((poly).c3))))
#define INTERVALS 5000
#define GET_INTERVAL(a, h, x) ((a) + (x) * (h))

typedef struct{
    double  c0,
            c1,
            c2,
            c3;
} Poly;

double eval_2d_poly(double arg, Poly cs){
    double res = cs.c3 * 3;
    res = res * arg + cs.c2 * 2;
    res = res * arg + cs.c1;
    return res;
}

double scholar_len(double t, double l, Poly xs, Poly ys, Poly zs){
    double xres = eval_2d_poly(t - l, xs);
    xres *= xres;
    double yres = eval_2d_poly(t - l, ys);
    yres *= yres;
    double zres = eval_2d_poly(t - l, zs);
    zres *= zres;
    return sqrt(xres + yres + zres);
}

double simpson_len(double a, double b, Poly xs, Poly ys, Poly zs){
    double  rsum = 0,
            h = (b - a) / INTERVALS;
    for (int j = 1; j <= INTERVALS / 2; j++) {
        rsum +=     scholar_len(GET_INTERVAL(a, h, 2 * j - 2), a, xs, ys, zs)
                    +
                    scholar_len(GET_INTERVAL(a, h, 2 * j - 1), a, xs, ys, zs) * 4
                    +
                    scholar_len(GET_INTERVAL(a, h, 2 * j), a, xs, ys, zs);
    }

    return h / 3 * rsum;
}

int main() {
    FILE    *fi = fopen("input.txt", "r"),
            *fo = fopen("output.txt", "w");

    int spans;
    fscanf(fi, "%d", &spans);
    Poly xs, ys, zs;
    double res = 0;
    double left, right;

    for (int i = 0; i < spans; i++) {
        fscanf(fi, "%lf%lf", &left, &right);
        SCANPOLY(xs);
        SCANPOLY(ys);
        SCANPOLY(zs);
        res += simpson_len(left, right, xs, ys, zs);
    }

    fprintf_s(fo, "%.20lf", res);
    fclose(fi);
    fclose(fo);
    return 0;
}
