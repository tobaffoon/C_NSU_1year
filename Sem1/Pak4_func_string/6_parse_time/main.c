#include <stdio.h>
#define LEN 15
int readTime ( char* iStr , int* oHours , int* oMinutes , int* oSeconds ){
    int hour_temp=-2, minute_temp=-2, sec_temp=-2, scan_temp=0, line_count=0, line_okay=1;
    char* inner_ptr = iStr;
    while(1){
        if(hour_temp > 23 || sscanf(inner_ptr, "%c", &scan_temp) == EOF){
            hour_temp = -1;
            if(oMinutes != NULL){
                minute_temp = -1;
                if(oSeconds != NULL) sec_temp = -1;
            }
            break;
        }
        inner_ptr++;
        line_count++;
        if (!(line_count == 1 || line_count == 2)) line_okay = 2;
        if(scan_temp == '|') {
            line_count -= 2;
            if (line_okay != 2) {
                line_okay = 0;
            }
            continue;
        }
        if(scan_temp == ':' && hour_temp!=-2){
            break;
        }
        hour_temp = (hour_temp == -2)?0:(hour_temp*10);
        hour_temp += scan_temp - '0';
    }
    while(1){
        if(hour_temp ==-1 || minute_temp > 59){
            hour_temp = -1;
            minute_temp = -1;
            sec_temp = -1;
            break;
        }
        inner_ptr++;
        if (((sscanf(inner_ptr, "%c", &scan_temp) == EOF) || scan_temp == ':') && minute_temp != -2) {
            if(scan_temp != ':'){
                inner_ptr--;
                sec_temp=0;
            }
            break;
        }
        line_count++;
        if (!(line_count == 1 || line_count == 2)) line_okay = 2;
        if(scan_temp == '|') {
            line_count -= 2;
            if (line_okay != 2) {
                line_okay = 0;
            }
            continue;
        }
        minute_temp = (minute_temp == -2) ? 0 : (minute_temp * 10);
        minute_temp += scan_temp - '0';
    }
    while(1){
        if(minute_temp == -1 || sec_temp > 59){
            hour_temp = -1;
            minute_temp = -1;
            sec_temp = -1;
            break;
        }
        inner_ptr++;
        if (sscanf(inner_ptr, "%c", &scan_temp) == EOF && sec_temp != -2) {
            break;
        }
        line_count++;
        if (!(line_count == 1 || line_count == 2)) line_okay = 2;
        if(scan_temp == '|') {
            line_count -= 2;
            if (line_okay != 2) {
                line_okay = 0;
            }
            continue;
        }
        sec_temp = (sec_temp == -2) ? 0 : (sec_temp * 10);
        sec_temp += scan_temp - '0';
    }
    if(!line_okay){
        hour_temp = -1;
        minute_temp = -1;
        sec_temp = -1;
    }
    *oHours = hour_temp;
    if(oMinutes != NULL){
        *oMinutes = minute_temp;
        if(oSeconds != NULL){
            *oSeconds = sec_temp;
        }
    }
    if(hour_temp == -1) return 0;
    else return 1;
}
int main() {
    char str[LEN];
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    scanf("%s", str);
    int call_h, call_m, call_s, res;
    int* call_h_ptr = &call_h;
    int* call_m_ptr = &call_m;
    int* call_s_ptr = &call_s;
    res = readTime(str, call_h_ptr, call_m_ptr, call_s_ptr);
    printf("%d %d %d %d", res, call_h, call_m, call_s);
    res = readTime(str, call_h_ptr, call_m_ptr, NULL);
    printf("\n%d %d %d", res, call_h, call_m);
    res = readTime(str, call_h_ptr, NULL, NULL);
    printf("\n%d %d", res, call_h);
    return 0;
}
