#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <mem.h>
int merge (const int *a, int ak, const int *b, int bk, int *res){
    while(ak && bk){
        if(*a < *b){
            *res = *a;
            ak--;
            if(ak) a++;
        }
        else{
            *res = *b;
            bk--;
            if(bk) b++;
        }
        res++;
    }
    if(ak == 0) memcpy(res, b, bk*sizeof(int32_t));
    else memcpy(res, a, ak*sizeof(int32_t));
    return 1;
}
int main() {
    FILE *fi, *fo;
    fi = fopen("input.txt", "rb");
    fo = fopen("output.txt", "wb");
    int32_t fst_count, snd_count;
    fread(&fst_count, sizeof(int32_t), 1, fi);
    fread(&snd_count, sizeof(int32_t), 1, fi);
    int32_t *fst = malloc(sizeof(int32_t) * fst_count);
    fread(fst, sizeof(int32_t), fst_count, fi);
    int32_t *snd = malloc(sizeof(int32_t) * snd_count);
    fread(snd, sizeof(int32_t), snd_count, fi);
    int32_t *res = malloc(sizeof(int32_t) * (fst_count+snd_count));
    merge(fst, fst_count, snd, snd_count, res);
    fwrite(res, sizeof(int32_t), (fst_count+snd_count), fo);
    fclose(fi);
    fclose(fo);
    return 0;
}
