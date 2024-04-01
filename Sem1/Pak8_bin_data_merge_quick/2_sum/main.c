#include <stdio.h>
#include <stdint.h>
void close_fi_fo(FILE *f1, FILE *f2){
    fclose(f1);
    fclose(f2);
}
void to_another_endianess32(uint32_t *a){
    uint32_t l = (*a >> 24);
    l += (*a >> 8) & 0x0000FF00;
    l += (*a << 8) & 0x00FF0000;
    l += (*a << 24);
    *a = l;
}
int main() {
//    FILE *fi = fopen("input.txt", "rb");
//    FILE *fo = fopen("output.txt", "wb");
    FILE *fi = fopen("1.in", "rb");
    FILE *fo = fopen("1.out", "wb");
    uint32_t n, cur, sum = 0;
    fread(&n, sizeof(n), 1, fi);
    if(n < 1 || n > 100000) {
        to_another_endianess32(&n);
        for(int i = 0; i < n; i++){
            fread(&cur, sizeof(cur), 1, fi);
            to_another_endianess32(&cur);
            sum += cur;
        }
        to_another_endianess32(&sum);
    }
    else{
        for(int i = 0; i < n; i++){
            fread(&cur, sizeof(cur), 1, fi);
            sum += cur;
        }
    }
    fwrite(&sum, sizeof(sum), 1, fo);;
    close_fi_fo(fi, fo);
    return 0;
}
