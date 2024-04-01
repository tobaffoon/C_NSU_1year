#include <stdio.h>
#include <stdint.h>
void close_fi_fo(FILE *f1, FILE *f2){
    fclose(f1);
    fclose(f2);
}
int main() {
    FILE *fi = fopen("input.txt", "rb");
    FILE *fo = fopen("output.txt", "wb");
    int32_t a,b;
    fread(&a, sizeof(a), 1, fi);
    fread(&b, sizeof(b), 1, fi);
    int64_t res = (int64_t)a + (int64_t)b;
    res >>= 1;
    fwrite(&res, sizeof(a), 1, fo);
    close_fi_fo(fi, fo);
    return 0;
}
