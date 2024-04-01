#include <stdio.h>
typedef unsigned int uint;
void print_sub_arr(){
    uint help=0;
    uint edge = ~help;
    uint mask;
    for(help; help<edge; help++){
        printf("{");
        for(int i =0; i<32; i++){
            if(help&mask){
                printf("%d ", i);
            }
            mask<<=1;
        }
        mask=1;
        printf("}\n");
    }
    printf("{");
    for(int i =0; i<32; i++){
        if(help&mask){
            printf("%d ", i);
        }
        mask<<=1;
    }
    printf("}");
}
int main() {
    print_sub_arr();
    return 0;
}
