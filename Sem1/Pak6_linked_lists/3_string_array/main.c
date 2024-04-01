#include <stdio.h>
#include <stdlib.h>
#define LEN 100002
int count_enters(const char* word, char cmp){
    int count=0, i=0;
    while(word[i]){
        if(cmp==word[i]) count++;
        i++;
    }
    return count;
}
int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    char *words[LEN];
    int requests, operation, idcnt=0;
    scanf("%d", &requests);
    for(int i=0; i<requests; i++){
        scanf("%d", &operation);
        if(operation){
            int idx;
            scanf("%d", &idx);
            if(operation==1){
                words[idx]=NULL;
                free(words[idx]);
                continue;
            }
            if(operation==2){
                printf("%s\n", words[idx]);
                continue;
            }
            char cmp_symb;
            scanf(" %c", &cmp_symb);
            printf("%d\n", count_enters(words[idx], cmp_symb));
            continue;
        }
        int len;
        scanf("%d", &len);
        words[idcnt] = malloc(sizeof(char)*len);
        scanf("%s", words[idcnt]);
        idcnt++;
    }
    for(int i = 0; i<idcnt; i++){
        if(words[i]!=NULL) free(words[i]);
    }
    return 0;
}
