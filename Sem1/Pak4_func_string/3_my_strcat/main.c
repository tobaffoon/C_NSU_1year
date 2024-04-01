#include <stdio.h>
#define LEN 1000002
int my_strlen(char* str){
    int count=0;
    while(str[count]){
        count++;
    }
    return count;
}
char* my_concat(char* pref, char* suff){
    pref += my_strlen(pref);
    for(suff; *suff; suff++){
        *pref = *suff;
        pref++;
    }
    *pref = '\0';
    return pref;
}
int main() {
    int n;
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    scanf("%d", &n);
    char word[LEN], word_next[101];
    scanf("%s", word);
    char *word_null_ptr = word+my_strlen(word)-1;
    for(int i=1; i<n; i++){
        scanf("%s", word_next);
        word_null_ptr = my_concat(word_null_ptr, word_next);
    }
    printf("%s", word);
    return 0;
}
