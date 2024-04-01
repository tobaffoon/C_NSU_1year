#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
//reads string from binary file, returns the number of chars that were read
uint64_t fread_string_bin(FILE *src, char *dest){
    int32_t length = 0;
    char current;
    do{
        fread(&current, sizeof(char), 1, src);
        *dest = current;
        dest++;
        length++;
    }while(current != 0);
    return length;
}
//both reads bson and writes json
uint64_t scan_and_load_field(FILE *src, FILE *dest){
    int8_t type;
    //remembers how many bytes we have read
    uint64_t read_bytes = sizeof(int8_t) * fread(&type, sizeof(int8_t), 1, src);
    char *name = malloc(1024);
    read_bytes += fread_string_bin(src, name);
    fprintf(dest, "\t\"%s\": ", name);
    //double case
    if(type == 1){
        double res;
        //as fread returns the number of elements of _ElementSize size, we need to multiply the result by _ElementSize to know how many bytes we have read
        read_bytes += sizeof(double) * fread(&res, sizeof(double), 1, src);
        fprintf(dest, "%0.15g", res);
    }
    //string case
    else if(type == 2){
        int32_t length;
        read_bytes += sizeof(int32_t) * fread(&length, sizeof(int32_t), 1, src);
        char *res = malloc(1024);
        read_bytes += sizeof(char) * fread(res, sizeof(char), length, src);
        fprintf(dest, "\"%s\"", res);
        free(res);
    }
    //bool case
    else if(type == 8){
        int8_t res;
        read_bytes += sizeof(char) * fread(&res, sizeof(char), 1, src);
        if(res == 0) fprintf(dest, "false");
        else fprintf(dest, "true");
    }
    //null case
    else if(type == 10){
        fprintf(dest, "null");
    }
    //int32 case
    else if(type == 16){
        int32_t res;
        read_bytes += sizeof(int32_t) * fread(&res, sizeof(int32_t), 1, src);
        fprintf(dest, "%d", res);
    }
    //int64 case
    else if(type == 18){
        int64_t res;
        read_bytes += sizeof(int64_t) * fread(&res, sizeof(int64_t), 1, src);
        fprintf(dest, "%lld", res);
    }
    fprintf(dest, ",\n");
    free(name);
    return read_bytes;
}
int main() {
    FILE *fi, *fo;
    fi = fopen("input.txt", "rb");
    fo = fopen("output.txt", "wt");
    uint64_t size;
    fread(&size, sizeof(int32_t), 1, fi);
    //we dismiss the first bytes that describe size and the last zero symbol
    size-=5;
    fprintf(fo, "{\n");
    while(size > 0){
        size -= scan_and_load_field(fi, fo);
    }
    fprintf(fo, "}");
    fclose(fi);
    fclose(fo);
    return 0;
}
