#include "modular.h"
#include <assert.h>

int main() {
    MOD = 29;
    long long a;

    a = -343;
    a = pnorm (a);
    assert (a == 5);

    a = 343;
    a = pnorm (a);
    assert (a == 24);

    a = padd(28, 27);
    assert (a == 26);

    a = psub(1, 20);
    assert (a == 10);

    a = psub(28, 20);
    assert (a == 8);

    a = pmul(9, 22);
    assert(a == 24);

    a = pdiv(9, 22);
    assert(a == 7);

    a = pdiv(22, 9);
    assert(a == 25);

    MOD = 982451653;

    a = padd(982451649, 982451353);
    assert (a == 982451349);

    a = psub(972451653, 2);
    assert (a == 972451651);

    a = pmul(982451649, 982451353);
    assert(a == 1200);

    a = pdiv(982451353, 1200);
    assert(a == 245612913);
    return 0;
}
