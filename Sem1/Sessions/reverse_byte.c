#include <stdio.h>
void swap(unsigned int *num){
    unsigned int res = 0;
    char *byte;
    for(int i = sizeof(*num)-1; i>=0; i--){
        byte = (char *) num;
        res |= (*byte << (8*i));
        *num = *num >> 8;
    }
    *num = res;
}
int main() {
    unsigned int my = 5;
    my = my << (24);
    swap(&my);
    printf("%d", my);
    return 0;
}
