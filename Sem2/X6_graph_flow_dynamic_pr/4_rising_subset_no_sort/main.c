#include <stdio.h>
#include <stdlib.h>

//DP array type
typedef struct DP{
	int sub_len,    //max number of elements that can come after the element
	next;      //id of what element to choose next to get the gr_num of elements
} DP;

int main(){
	FILE *fi = fopen("input.txt", "r"),
			*fo = fopen("output.txt", "w");
	int N;                                                                                          //Initial array length
	fscanf(fi, "%d", &N);

	int *arr = malloc(N * sizeof(int));                                                             //Initial array
	for(int i = 0; i < N; i++) {
		fscanf(fi, "%d", &(arr[i]));                                                                //read element value
	}
	DP *dp = malloc(N * sizeof(DP));                                                                //array containing number
	DP start = {0, -1};                                                                             //"head" of dynamic programming - to know what the first elem should be
	for(int step = N-1; step >= 0; step--) {
		dp[step].sub_len=1;                                                                         //initially choosing only this elem we can get 1 element in growing sub array
		dp[step].next=-1;                                                                           //if only this elem is chosen, no elem comes next
		for(int next_id = step + 1; next_id < N; next_id++) {                                       //find where we can jump to make longest sub array
			if(arr[next_id] > arr[step]){                                                           //we can try to jump to next only if it is larger than current elem
				if(dp[next_id].sub_len >= dp[step].sub_len){                                        //choose next only if we can gain larger sub array
					dp[step].sub_len = dp[next_id].sub_len + 1;                                     //longest sub array also contains current elem (thus +1)
					dp[step].next = next_id;                                                        //where we should jump to gain longest sub array
				}
			}
		}
		if(dp[step].sub_len > start.sub_len){                                                       //remember the longest sub array we know so far
			start.sub_len = dp[step].sub_len;
			start.next = step;
		}
	}

	fprintf(fo, "%d\n", start.sub_len);
	while(start.next != -1){
		fprintf(fo, "A[%d] = %d\n", start.next+1, arr[start.next]);
		start = dp[start.next];
	}

	fclose(fi);
	fclose(fo);
	return 0;
}