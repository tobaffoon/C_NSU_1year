#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#pragma pack(push,1)
typedef struct File_s{
    char name[21];
    uint64_t size;
    uint8_t is_dir;
    uint64_t creation_time;
    uint64_t mod_time;
    uint8_t is_hidden;
} File_s;
#pragma pack(pop)
/*void File_s_copy(File_s *src, File_s* dst){
    strcpy(src->name, dst->name);
    src->size = dst->size;
    src->is_dir = dst->is_dir;
    src->creation_time = dst->creation_time;
    src->mod_time = dst->mod_time;
    src->is_hidden = dst->is_hidden;
}*/
/*void print_num(uint8_t *pr, size_t pr_size){
    for(int i = 0; i < pr_size; i++){
        printf("%d ", *pr);
        pr++;
    }
    printf("\n");
}*/
/*void print_names(File_s *pr, FILE *f, int true){
    for(int i = 0; i < true; i++){
        fprintf(f, "%s ", pr[i].name);
    }
    fprintf(f, "\n");
}*/
void file_quicksort1(File_s *list, uint32_t first, uint32_t last){
    if (first < last){
        uint32_t l = first, r = last;
        char *mid = (list + (l + r) / 2)->name;
        do{
            while (strcmp((list + l)->name, mid) < 0) l++;
            while (strcmp((list + r)->name, mid) > 0) r--;
            if (l <= r){
                File_s tmp = list[l];
                list[l] = list[r];
                list[r] = tmp;
                l++;
                r--;
            }
        }while (l <= r);
        file_quicksort1(list, first, r);
        file_quicksort1(list, l, last);
    }
}
void file_quicksort(File_s *list, uint32_t size){
    file_quicksort1(list, 0, size-1);
}
void file_bubblesort(File_s *list, uint32_t size){
    size--;
    for(int i = 0; i < size; i++){
        uint32_t sizei = size - i;
        for(int j = 0; j < sizei; j++){
            if(strcmp(list[j].name, list[j+1].name) > 0){
                File_s temp = list[j];
                list[j] = list[j+1];
                list[j+1] = temp;
            }
        }
    }
}
void convert_to_another_endianess(uint8_t *a, size_t num_size){
    uint8_t *temp = malloc(num_size);
    a += num_size - 1;
    for(int i = 0; i < num_size; i++){
        *temp = *a;
        temp++;
        a--;
    }
    temp -= num_size;
    for (int i = 0; i < num_size; i++) {
        a++;
        *a = *temp;
        temp++;
    }
    free(temp);
}
void convert_File_s_to_another_endianess(File_s *file){
    convert_to_another_endianess((uint8_t *)((char*)file + (char)offsetof(File_s, is_dir)), sizeof(file->is_dir));
    convert_to_another_endianess((uint8_t *)((char*)file + (char)offsetof(File_s, creation_time)), sizeof(file->creation_time));
    convert_to_another_endianess((uint8_t *)((char*)file + (char)offsetof(File_s, mod_time)), sizeof(file->mod_time));
    convert_to_another_endianess((uint8_t *)((char*)file + (char)offsetof(File_s, is_hidden)), sizeof(file->is_hidden));
}
uint32_t sort_by_time_period(File_s *file, uint32_t n, uint64_t creation_time, uint64_t mod_time){
    uint32_t useful = n;
    for(int i = 0; i < n; i++){
        if(file->is_dir || file->is_hidden || file->creation_time < creation_time || file->mod_time > mod_time){
            strcpy(file->name, "!\0");
            useful--;
        }
        file++;
    }
    file -= n;
    file_bubblesort(file, n);
    return useful;                          //returns number of files that fit our criteria
}
int main() {
    FILE *fi, *fo;
//    fi = fopen("4 (2).in", "rb");
//    fo = fopen("1.out", "wb");
    fi = fopen("input.txt", "rb");
    fo = fopen("output.txt", "wb");
    uint32_t num_f;
    uint64_t cmp_cr_time, cmp_mod_time;
    fread(&num_f, sizeof(num_f), 1, fi);                    //read number of files and date boarders
    fread(&cmp_cr_time, sizeof(cmp_cr_time), 1, fi);
    fread(&cmp_mod_time, sizeof(cmp_mod_time), 1, fi);
    File_s *list = malloc(sizeof(File_s) * num_f);
    fread(list, sizeof(File_s), num_f, fi);
    uint32_t new_num = sort_by_time_period(list, num_f, cmp_cr_time, cmp_mod_time);
    fwrite((list + (num_f - new_num)), sizeof(File_s), new_num, fo);
    fclose(fi);
    fclose(fo);
    free(list);
    return 0;                               
}
