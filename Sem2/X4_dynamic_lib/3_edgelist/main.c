#include <assert.h>
#include "sol.h"

int main() {
    init();
    int num = getEdgesCount(0);
    assert(num == 2);


    num = getEdgesCount(1);
    assert(num == 4);


    num = getEdgesCount(2);
    assert(num == 2);


    num = getEdgesCount(3);
    assert(num == 1);
    Edge e = getIncidentEdge(3, 0);
    assert(e.from == 3 && e.to == 4 && e.weight == 207);

    num = getEdgesCount(5);
    assert(num == 0);
//    e = getIncidentEdge(5, 0);

    num = getEdgesCount(4);
    assert(num == 3);

    return 0;
}
