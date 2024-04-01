#include <stdio.h>
#include <string.h>
typedef struct Label_s {
    char name [16];
    int age;
} Label;
typedef struct NameStats_s {
    int cntTotal;
    int cntLong;
} NameStats;
typedef struct AgeStats_s {
    int cntTotal;
    int cntAdults;
    int cntKids;
} AgeStats;
void calcStats (const Label *arr, int cnt, NameStats *oNames, AgeStats *oAges){
    for (int i = 0; i < cnt; i++) {
        if(strlen(arr[i].name)>10) oNames->cntLong++;
        if(arr[i].age >= 18) oAges->cntAdults++;
        else if(arr[i].age < 14) oAges->cntKids++;
    }
}
int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    int n;
    scanf("%d", &n);
    Label cur[1000];
    NameStats nstats = {n, 0};
    AgeStats astats = {n, 0, 0};
    for(int i=0; i<n; i++) scanf("%s %d let", cur[i].name, &cur[i].age);
    calcStats(cur, n, &nstats, &astats);
    printf("names: total = %d\n", nstats.cntTotal);
    printf("names: long = %d\n", nstats.cntLong);
    printf("ages: total = %d\n", astats.cntTotal);
    printf("ages: adult = %d\n", astats.cntAdults);
    printf("ages: kid = %d", astats.cntKids);
    return 0;
}
