#include <stdio.h>
#include "myblas.h"

int main() {
    /*double B[] =    {5, -5, 6, 7,
                     0.1, 0.05, 2, -3,
                     0.5, 4, -10, 3
                    };
    double A[] =   {2,  3,  4,
                    1,  11, 2,
                    -1, -2, -3};
    double C[] =    {1, 0, 0, 0,
                     0, 1, 0, 0,
                     0, 0, 1, 1};*/
    double A[] = {9, 2,
                  6, 5};
    double X[] = {6, 8};
    double Y[] = {4, 5};
    dger(2, 2, 5, X, Y, A);
    return 0;
}
