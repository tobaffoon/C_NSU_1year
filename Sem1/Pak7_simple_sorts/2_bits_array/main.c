#include <stdio.h>
#include <stdlib.h>
typedef unsigned int bitword;
char bitwl = sizeof(bitword) << 3;
void bitsetZero(bitword **arr, unsigned int num){
    if(*arr != NULL) free(*arr);
    *arr = malloc((bitwl >> 3) * num);
    for(unsigned int i = 0; i<num; i++){
        **arr &= (bitword)0;
        *arr = *arr + 1;
    }
    *arr = *arr - num;
}
/*void print_bitset(bitword *arr, int num){
    for(int i = 0; i<num; i++){
        printf("%d\n", *arr);
        arr++;
    }
}*/
unsigned int bitsetGet(const bitword *arr, unsigned int idx){
    arr += (idx / bitwl);
    idx = bitwl - 1 - idx % bitwl;
    return ((*arr >> idx) & (char)1);
}
void bitsetSet(bitword *arr, unsigned int idx, char newval){
    arr += (idx / bitwl);
    idx = bitwl - 1 - idx % bitwl;
    *arr = (*arr & ~((char)1 << idx)) | (newval << idx);
}
int bitsetAny(const bitword *arr, unsigned int left, unsigned int right){
    unsigned int word_left = left / bitwl, word_right = right / bitwl;
    bitword res;
    arr = arr + word_left;
    /*if(left == right){
        right = bitwl - right % bitwl;
        if(*arr & ((bitword)1 << (right - 1))){
            return 1;
        }
        return 0;
    }*/
    left = left % bitwl;
    right = bitwl - right % bitwl;
    if(word_left == word_right){
        res = ((~(bitword)0 >> left) & (~(bitword)0 << right)) & *arr;
        if(right == bitwl) res = 0;
        if(res) return 1;
        return 0;
    }
    res = (~(bitword)0 >> left) & *arr;
    if(res) return 1;
    arr++;
    word_left++;
    while(word_left != word_right){
        if(*arr) return 1;
        arr++;
        word_left++;
    }
    if (right == bitwl) res = (bitword)0;
    else res = (~(bitword)0 << right);
    res &= *arr;
    if(res) return 1;
    return 0;
}
int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    unsigned int num_of_operations, cur_operation, len;
    bitword *words = NULL;
    scanf("%u", &num_of_operations);
    for(int i = 0; i < num_of_operations; i++){
        scanf("%u", &cur_operation);
        if(cur_operation == 0){
            scanf("%u", &len);
            len = (len - 1) / bitwl + 1;
            bitsetZero(&words, len);
            continue;
        }
        if(cur_operation == 1){
            unsigned int id;
            scanf("%u", &id);
            printf("%u\n", bitsetGet(words, id));
            continue;
        }
        if(cur_operation == 2){
            unsigned int id;
            char val;
            scanf("%u %c", &id, &val);
            val-='0';
            bitsetSet(words, id, val);
            continue;
        }
        unsigned int lbord, rbord;
        scanf("%u %u", &lbord, &rbord);
        if(bitsetAny(words, lbord, rbord)) {
            printf("some\n");
            continue;
        }
        printf("none\n");
    }
    return 0;
}
