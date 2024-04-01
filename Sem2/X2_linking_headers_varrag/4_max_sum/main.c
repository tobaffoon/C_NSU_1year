#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
int     len;
int     *as;
extern int64_t *subsum;

extern int Query(int l, int64_t sum);
extern void Init(const int *arr, int len);

//same file
int main() {
    FILE    *fi = fopen("input.txt", "r"),
            *fo = fopen("output.txt", "w");

    int q,
        curq;

    int64_t   curs;

    fscanf(fi, "%d%d", &len, &q);
    as = malloc(len * sizeof(int));

    for (int i = 0; i < len; i++) {
        fscanf(fi, "%d", as + i);
    }

    Init(as, len);

    for (int i = 0; i < q; i++) {
        fscanf(fi, "%d%lld", &curq, &curs);
        int r = Query(curq, curs);
        fprintf_s(fo, "%d\n", r);
    }

    free(subsum);

    fclose(fi);
    fclose(fo);
    return 0;
}
