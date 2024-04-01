#include <stdio.h>
#define VALUE_BITS (CHAR_BITS * sizeof(unsigned long))
unsigned long bit_count (unsigned long value){
    value = (value & 0x55555555) + ((value>>1) & 0x55555555);
    value = (value & 0x33333333) + ((value>>2) & 0x33333333);
    value = (value & 0x0F0F0F0F) + ((value>>4) & 0x0F0F0F0F);
    value = (value & 0x00FF00FF) + ((value>>8) & 0x00FF00FF);
    value = (value & 0x0000FFFF) + ((value>>16) & 0x0000FFFF);
    return value;
}
int zer_bit_count (unsigned int value){
    value = (value & 0x55555555) + ((value>>1) & 0x55555555);
    value = (value & 0x33333333) + ((value>>2) & 0x33333333);
    value = (value & 0x0F0F0F0F) + ((value>>4) & 0x0F0F0F0F);
    value = (value & 0x00FF00FF) + ((value>>8) & 0x00FF00FF);
    value = (value & 0x0000FFFF) + ((value>>16) & 0x0000FFFF);
    return (32-value);
}
unsigned long bit_count1 (unsigned long value){                                   //count_table - число единичных битов в каждом бите
    static const unsigned char count_table[] = {0,1,1,2,1,3,1,4};                 //static живут во внешней памяти, но видятся локально - нужно, чтобы сохранять значения и похже использовать их в тех же функциях
    int count = 0;
    while(value!=0){
        count+=count_table[value&0xFF];
        value>>=8;
    }
    return count;
}
int main() {
    printf("%u", bit_count(0x0F0F0F0E));
    return 0;
}
