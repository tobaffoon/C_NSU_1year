#include <stdio.h>
#include <string.h>
typedef struct LongNum_s {
    int len;
    unsigned char arr[1000];                                            //We store two digits (as digits, so -'0') in one char, len corresponds with the amount of pairs
} LongNum;
void longstrcpy(LongNum *dest, LongNum *src){                           //We need new strcpy, because arr can contain 0
    for(int j=0; j<src->len; j++){
        dest->arr[j]=src->arr[j];
    }
}
void num_to_normal_form(unsigned int added_num, LongNum *n, int idx){   //To safely add a number to n, starting from idx and moving to idx+1 if the result is > 99
    if(idx==n->len) n->len++;                                           //We need to make "lengthen" the arr, so that if we change the pair that is out of reach - we fix it
    n->arr[idx]+=added_num%100;
    added_num-=added_num%100;
    if(n->arr[idx]>99){
        added_num+=n->arr[idx];
        n->arr[idx]=n->arr[idx]%100;
    }
    if(added_num!=0){
        num_to_normal_form(added_num/100, n, idx+1);
    }
}
void longmult(char mult1, LongNum *dest, LongNum *templte, int cur_digit){  //Here we add up our accumulator 'res' (look at longmult_full)
    unsigned int a;                                                         //and our original number multiplied by 2 digits and 10 to the (2*pair id)th power
    for(int j=0; j < templte->len; j++){
        a=templte->arr[j]*mult1;
        num_to_normal_form(a, dest, j+cur_digit);                       //We add up numbers only form j+cur_digit position, because previous ones look like: 00+dest[j].
    }                                                                       //It's useless to change this digits
}
void longmult_full(LongNum *n, LongNum *m){
    LongNum res = {1, 0};
    for (int i = 0; i < m->len; i++){
        longmult(m->arr[i], &res, n, i);
    }
    n->len=res.len;
    longstrcpy(n, &res);
}
void long_prnt(LongNum *s){
    printf("%d",(s->arr)[s->len-1]);                                //We don't need %02d, because if the greatest char is 3, we don't want a leading zero to appear
    for(int i=s->len-2; i>=0; i--){
        printf("%02d",(s->arr)[i]);                                 //We need %02d, because if char contains 3, we should print 03
    }
}
int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    LongNum a, b;
    char temp[1001];                                                       //I think it is faster to read a string and reverse it, than fill the arr on the spot
    scanf("%s", temp);
    a.len=strlen(temp);
    for(int i = 0; i < a.len-1; i+=2){                                     //We don't read the last digit, if
        temp[a.len-i-1]-='0';
        temp[a.len-i-2]-='0';
        a.arr[i/2]=temp[a.len-i-1]+10*temp[a.len-i-2];
    }
    if(a.len%2==1){                                                        //If len is odd only read one first (greatest) digit
        a.arr[a.len/2]=temp[0]-'0';
    }
    a.len=(a.len+1)/2;                                                     //We count number of pairs (even the ones consisting of 1 digit)
    scanf("%s", temp);
    b.len=strlen(temp);
    for(int i = 0; i < b.len-1; i+=2){
        temp[b.len-i-1]-='0';
        temp[b.len-i-2]-='0';
        b.arr[i/2]=temp[b.len-i-1]+10*temp[b.len-i-2];
    }
    if(b.len%2==1){
        b.arr[b.len/2]=temp[0]-'0';
    }
    b.len=(b.len+1)/2;
    longmult_full(&a, &b);
    long_prnt(&a);
    return 0;
}