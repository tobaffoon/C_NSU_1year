#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Elem{
	int val,
			id;
} Elem;

//DP array type
typedef struct DP{
	int sub_len,    //max number of elements that can come after the element
	next;      //id of what element to choose next to get the gr_num of elements
} DP;

//merge of two arrays function
void merge (Elem *a, int ak, Elem *b, int bk){
	int totalk = ak+bk;
	Elem *buf = malloc(sizeof(Elem) * (totalk)), *a1 = a;
	while(ak && bk){
		if(a[0].val <= b[0].val){
			buf[0] = a[0];
			ak--;
			a++;
		}
		else{
			buf[0] = b[0];
			bk--;
			b++;
		}
		buf++;
	}
	if(ak == 0) {
		memcpy(buf, b, bk * sizeof(Elem));
		buf -= totalk - bk;
	}
	else{
		memcpy(buf, a, ak * sizeof(Elem));
		buf -= totalk - ak;
	}
	a = a1;
	memcpy(a, buf, totalk*sizeof(Elem));
	free(buf);
}

//main merge sort function with Elem type
Elem* merge_sort(Elem *a, int size){
	if(size > 2){
		merge(merge_sort(a, size/2), size/2, merge_sort(a + size/2, (size+1)/2), (size+1)/2);
	}
	else if(size != 1 && a[0].val > a[1].val){
		Elem temp = a[0];
		a[0] = a[1];
		a[1] = temp;
	}
	return a;
}

int main(){
	FILE *fi = fopen("input.txt", "r"),
			*fo = fopen("output.txt", "w");
	int N;                                                                                          //Initial array length
	fscanf(fi, "%d", &N);

	Elem *arr = malloc(N * sizeof(Elem));                                                           //Initial array
	for(int i = 0; i < N; i++) {
		fscanf(fi, "%d", &(arr[i].val));                                                            //read element value
		arr[i].id=i;                                                                                //load element index
	}
	//as we look for both increasing values and indices, we can sort the array by values
	//to work only with indices which span [0...N-1]
	merge_sort(arr, N);                                                                             //merge sort with Elem type

	DP *dp = malloc(N * sizeof(DP));                                                                //array containing number
	DP start = {0, -1};                                                                             //"head" of dynamic programming - to know what the first elem should be
	for(int step = N-1; step >= 0; step--) {
		dp[step].sub_len=1;                                                                         //initially choosing only this elem we can get 1 element in growing sub array
		dp[step].next=-1;                                                                           //if only this elem is chosen, no elem comes next
		for(int next_id = step + 1; next_id < N; next_id++) {                                       //find where we can jump to make longest sub array
			if(arr[next_id].id > arr[step].id && arr[next_id].val != arr[step].val){                //we can try to jump to next only if it is larger than current elem
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
		fprintf(fo, "A[%d] = %d\n", arr[start.next].id+1, arr[start.next].val);
		start = dp[start.next];
	}

	fclose(fi);
	fclose(fo);
	return 0;
}