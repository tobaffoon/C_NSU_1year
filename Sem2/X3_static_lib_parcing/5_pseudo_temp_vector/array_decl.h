#define TCAT2(a, b) a##_##b
#define CAT2(a, b) TCAT2(a, b)

typedef struct NAME {
    int n,
            cap;
    TYPE *arr;
} NAME;

void    CAT2(NAME, init)(NAME *vec);

void    CAT2(NAME, destroy)(NAME *vec);

int     CAT2(NAME, push)(NAME *vec, TYPE value);

TYPE    CAT2(NAME, pop)(NAME *vec);

void    CAT2(NAME, reserve)(NAME *vec, int capacity);

void    CAT2(NAME, resize)(NAME *vec, int newCnt, TYPE fill);

void    CAT2(NAME, insert)(NAME *vec, int where, TYPE *arr, int num);

void    CAT2(NAME, erase)(NAME *vec, int where, int num);

#undef TYPE
#undef NAME
