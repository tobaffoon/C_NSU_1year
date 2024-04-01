#include <stdio.h>

int main() {
    int d,m,y,k;
    scanf("%d%d%d%d", &d,&m,&y,&k);
    while(k>366){
        if( (((y%4==0 && y%100!=0) || y%400==0) && m<=2) || ((((y+1)%4==0 && (y+1)%100!=0) || (y+1)%400==0) && m>2)){
            k--;
        }
        y++;
        k-=365;
    }
    d+=k;
    while(d){
        if(m==1 || m==3 || m==5 || m==7 || m==8 || m==10){
            if(d<=31) break;
            d-=31;
            m++;
        }
        else if(m==4 || m==6 || m==9 || m==11){
            if(d<=30) break;
            d-=30;
            m++;
        }
        else if(m==2){
            if(d<=28 || (d==29 && ((y%4==0 && y%100!=0) || y%400==0))) break;
            d-=28;
            if((y%4==0 && y%100!=0) || y%400==0){
                d--;
            }
            m++;
        }
        else{
            if(d<=31) break;
            d-=31;
            y++;
            m=1;
        }
    }
    printf("%d %d %d", d, m, y);
    return 0;
}
