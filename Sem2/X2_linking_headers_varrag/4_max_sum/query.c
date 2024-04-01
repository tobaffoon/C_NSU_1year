#include <stdint.h>
extern int len;
extern int *as;
int64_t *subsum;

extern void Init(const int *arr, int len);
extern int64_t Sum(int l, int r);

int bsrch_sum(int l, int r, int64_t comp){
    int64_t csum = Sum(l, r);
    if(csum <= comp)
        return r;
    int cand = r,
        cl = l,
        id;
    while(cl <= r){
        id = (cl + r) / 2;
        csum = Sum(l, id);
        if(csum <= comp){
            cand = id;
            cl = id + 1;
        }
        else{
            r = id - 1;
        }
    }
    return cand;
}

int Query(int l, int64_t sum){
    int res = bsrch_sum(l, len, sum);
    return res;
}