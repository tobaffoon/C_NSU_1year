#include <stdio.h>
#define LEN 1000
int int_len(int d){
    int digits=0;
    while(d>0){
        digits++;
        d/=10;
    }
    return digits;
}
void write_dash(int n){
    while(n--){
        printf("-");
    }
}
void write_space(int n){
    while(n--){
        printf(" ");
    }
}
int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    int n;
    scanf("%d", &n);
    int frag[LEN]={0};
    int dur[LEN]={0};
    int frag_temp, dur_temp, max_idx=0, max_frag=0, max_dur=0;
    for(int i = 0; i<n; i++){
        scanf("%d %d", &frag_temp, &dur_temp);
        int temp_digits = int_len(frag_temp);
        if(temp_digits > max_idx) max_idx=temp_digits;
        frag_temp--;
        temp_digits = int_len(++frag[frag_temp]);
        if(temp_digits > max_frag) max_frag=temp_digits;
        dur[frag_temp]+=dur_temp;
        temp_digits = int_len(dur[frag_temp]);
        if(temp_digits > max_dur) max_dur=temp_digits;
    }
    max_idx+=2;
    max_dur+=2;
    max_frag+=2;
    for(int i=0; i<LEN; i++){
        if(frag[i]){
            printf("+");
            write_dash(max_idx);
            printf("+");
            write_dash(max_frag);
            printf("+");
            write_dash(max_dur);
            printf("+\n|");
            int temp_digits = int_len(i+1);
            write_space(max_idx-temp_digits-1);
            printf("%d |", i+1);
            temp_digits = int_len(frag[i]);
            write_space(max_frag-temp_digits-1);
            printf("%d |", frag[i]);
            temp_digits = int_len(dur[i]);
            write_space(max_dur-temp_digits-1);
            printf("%d |\n", dur[i]);
        }
    }

    printf("+");
    write_dash(max_idx);
    printf("+");
    write_dash(max_frag);
    printf("+");
    write_dash(max_dur);
    printf("+");
    return 0;
}
