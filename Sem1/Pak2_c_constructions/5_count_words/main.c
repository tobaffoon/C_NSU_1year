#include <stdio.h>
char next(){
    char cur;
    do{
        scanf("%c", &cur);
    }while(cur!='.' && cur!='\n');
    return cur;
}
int main() {
    char c;
    int num=0;
    do{
        scanf("%c", &c);
        if(c!='.' && c!='\n'){
            num++;
            c=next();
        }
    }while(c!='\n');
    printf("%d", num);
    return 0;
}
