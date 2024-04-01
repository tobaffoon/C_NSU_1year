#include <stdio.h>
int fromLetters(char ch){
    if(ch>='0' && ch<='9') return (ch-'0');
    else return (ch-'a'+10);
}
char toLetters(int d){
    if(d<=9 && d>=0) return d+'0';
    else return d-10+'a';
}
int main() {
    FILE *fpr;
    fpr = fopen("input.txt", "r");
    int n,m;
    fscanf(fpr, "%d%d", &n, &m);
    int dec=0;
    char c;
    while(fscanf(fpr, "\n%c", &c) != EOF){
        dec*=n;
        dec+=fromLetters(c);
    }
    char final[30]={'\0'};
    int i=29;
    do{
        final[i]=toLetters(dec%m);
        dec/=m;
        i--;
    }while(dec>0);
    for(int i=0; i<30; i++){
        if(final[i]!='\0') printf("%c", final[i]);
    }
    fclose(fpr);
    return 0;
}
