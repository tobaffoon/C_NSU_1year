#include <stdlib.h>
#include <string.h>

void CAT2(NAME, init)(NAME *vec) {
    vec->n = 0;
    vec->cap = 100;
    vec->arr = malloc(sizeof(TYPE) * vec->cap);
}

void CAT2(NAME, destroy)(NAME *vec) {
    if (vec->cap == 0) {
        return;
    }
    vec->n = 0;
    vec->cap = 0;
    free(vec->arr);
}

int CAT2(NAME, push)(NAME *vec, TYPE value) {
    if (vec->cap == 0) {
        CAT2(NAME, init)(vec);
    }

    if (vec->n == vec->cap) {
        vec->cap *= 2;
        vec->arr = (TYPE *) realloc(vec->arr, sizeof(TYPE) * vec->cap);
    }
    vec->arr[vec->n] = value;

    return (vec->n)++;
}

TYPE CAT2(NAME, pop)(NAME *vec) {
    return (vec->arr[--vec->n]);
}

void CAT2(NAME, reserve)(NAME *vec, int capacity) {
    if (vec->cap == 0) {
        CAT2(NAME, init)(vec);
    }

    if ((vec->cap - vec->n) < capacity) {
        vec->cap += capacity;
//        vec->cap += capacity - (vec->cap - vec->n);
        vec->arr = (TYPE *) realloc(vec->arr, sizeof(TYPE) * vec->cap);
    }
}

void CAT2(NAME, resize)(NAME *vec, int newCnt, TYPE fill) {
    if (vec->cap == 0) {
        CAT2(NAME, init)(vec);
    }

    if (vec->n < newCnt) {
        CAT2(NAME, reserve)(vec, newCnt);
        while (vec->n < newCnt) {
            CAT2(NAME, push)(vec, fill);
        }
    }

    vec->n = newCnt;
}

void CAT2(NAME, insert)(NAME *vec, int where, TYPE *arr, int num) {
    if (num == 0) {
        return;
    }

    CAT2(NAME, reserve)(vec, num);

    //move elements to the right
    memcpy(vec->arr + where + num,
           vec->arr + where,
           sizeof(TYPE) * (vec->n - where));

    //fill acquired cells
    memcpy(vec->arr + where,
           arr,
           sizeof(TYPE) * num);

    vec->n += num;
}

void CAT2(NAME, erase)(NAME *vec, int where, int num) {
    if(vec->n < num){
        vec -> n = 0;
        return;
    }

    memcpy(vec->arr + where,
           vec->arr + where + num,
           sizeof(TYPE) * (vec->n - where - num));

    vec->n -= num;
}

#undef TYPE
#undef NAME