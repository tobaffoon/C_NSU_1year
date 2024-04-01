#include <stdio.h>
#include <stdlib.h>
#define DEM 5
#define SIZE (1<<DEM)

int main() {
    int* idx = malloc(SIZE);
    idx[0] = 0;
    idx[1] = 1;
    for (int i = 1; i <= DEM; i++) {
        int temp = (1<<i) - 1;
        for (int j = temp; j >= 0; j--) {
            idx[temp + temp - j + 1] = idx [j] + (1<<i);
        }
    }

    for (int i = 0; i < SIZE; i++) {
        printf("%d\n", idx[i]);
    }
    return 0;
}
