#include <stdio.h>
void print_time(int hour, int minute, int sec){
    printf("%02d:%02d:%02d\n", hour, minute, sec);
}
int main() {
    int n;
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    scanf("%d", &n);
    int hour_temp, minute_temp, sec_temp;
    for(int i = 0; i < n; i++){
        scanf("%d%d%d", &hour_temp, &minute_temp, &sec_temp);
        print_time(hour_temp, minute_temp, sec_temp);
    }
    return 0;
}
