#include <stdio.h>
#define LEN 50000
typedef struct DateTime_s {
int year , month , day ;
int hours , minutes , seconds ;
} DateTime ;
DateTime min ( const DateTime * arr, int cnt ){
  DateTime res;
  res.year = arr -> year;
  res.month = arr -> month;
  res.day = arr -> day;
  res.hours = arr -> hours;
  res.minutes = arr -> minutes;
  res.seconds = arr -> seconds;
  for(int i = 1; i < cnt; i++){
      arr++;
    if(arr -> year <= res.year){    //Если <, то меняем всё в res
      if(arr -> year == res.year){
        if(arr -> month <= res.month){
          if(arr -> month == res.month){
            if(arr -> day <= res.day){
              if(arr -> day == res.day){
                if(arr -> hours <= res.hours){
                  if(arr -> hours == res.hours){
                    if(arr -> minutes <= res.minutes){
                      if(arr -> minutes == res.minutes){
                        if(arr -> seconds <= res.seconds){
                          res.seconds = arr -> seconds;
                        }
                      }
                      else{
                          res.minutes = arr -> minutes;
                          res.seconds = arr -> seconds;
                      }
                    }
                  }
                  else{
                      res.hours = arr -> hours;
                      res.minutes = arr -> minutes;
                      res.seconds = arr -> seconds;
                  }
                }
              }
              else{
                  res.day = arr -> day;
                  res.hours = arr -> hours;
                  res.minutes = arr -> minutes;
                  res.seconds = arr -> seconds;
              }
            }
          }
          else{
              res.month = arr -> month;
              res.day = arr -> day;
              res.hours = arr -> hours;
              res.minutes = arr -> minutes;
              res.seconds = arr -> seconds;
          }
        }
      }
      else{
          res.year = arr -> year;
          res.month = arr -> month;
          res.day = arr -> day;
          res.hours = arr -> hours;
          res.minutes = arr -> minutes;
          res.seconds = arr -> seconds;
      }
    }
  }
  return res;
}
int main()
{
  int n;
  scanf("%d", &n);
  DateTime arDT[LEN];
  for(int i = 0; i<n; i++){
    scanf("%d %d %d %d %d %d", &arDT[i].year,&arDT[i].month,&arDT[i].day,&arDT[i].hours, &arDT[i].minutes, &arDT[i].seconds);
  }
  DateTime result = min(arDT, n);
  printf("%d %d %d %d %d %d", result.year,result.month,result.day,result.hours, result.minutes, result.seconds);
  return 0;
}