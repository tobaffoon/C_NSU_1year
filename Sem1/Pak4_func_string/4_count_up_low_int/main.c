#include <stdio.h>
int calcLetters(char* iStr, int* oLowerCnt, int* oUpperCnt, int* oDigitsCnt ){
    int lett = 0;
    while(iStr[lett]){
        if(iStr[lett] <= 'z' && iStr[lett] >= 'a') (*oLowerCnt)++;
        else if(iStr[lett] <= 'Z' && iStr[lett] >= 'A') (*oUpperCnt)++;
        else if(iStr[lett] <= '9' && iStr[lett] >= '0') (*oDigitsCnt)++;
        lett++;
    }
    return lett;
}
int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    char str[100];
    int low, upper, dig, i=1;
    while(gets(str) != NULL){
        low=0;
        upper=0;
        dig=0;
        printf("Line %d has %d chars: ", i, calcLetters(str, &low, &upper, &dig));
        printf("%d are letters (%d lower, %d upper), %d are digits.\n", low+upper, low, upper, dig);
        i++;
    }
    return 0;
}
