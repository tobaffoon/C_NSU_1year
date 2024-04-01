#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
typedef struct TLetter{
    uint8_t size;
    uint64_t value;
} letter;
void read_letter(letter *l, FILE* src){
    l -> value = 0;
    for(int i = 0; i < l -> size; i++){
        uint8_t temp;
        fread(&temp, sizeof(temp), 1, src);
        //values are stored in "big_endian", but not starting from the left bit, instead - ending at the right bit
        l -> value += temp << i;
    }
}
void fill_alphabet(letter *dest, uint32_t len, FILE* src){
    for(int i = 0; i < len; i++){
        uint32_t symb_len;
        fread(&symb_len, sizeof(symb_len), 1, src);
        dest -> size = symb_len;
        read_letter(dest, src);
        dest++;
    }
}
void interpret_and_print_word(uint64_t len, letter *alph, FILE *in,  FILE *out){
    for(int i = 0; i < len; i++){
        uint16_t idx;
        fread(&idx, sizeof(idx), 1, in);
    }
}
void print_letter(letter *l, FILE *dest){
    for(int i = 0; i < l -> size; i++) {

    }
}
int main() {
    FILE *fi, *fo;
    fi = fopen("input.txt", "rb");
    fo = fopen("output.txt", "wt");
    uint32_t length;    //length of the alphabet
    fread(&length, sizeof(length), 1, fi);
    letter *alphabet = malloc(length * sizeof(letter));
    fill_alphabet(alphabet, length, fi);
    return 0;
}
