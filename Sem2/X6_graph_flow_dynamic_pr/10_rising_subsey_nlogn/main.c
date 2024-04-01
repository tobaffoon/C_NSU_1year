#include <stdio.h>
#include <stdlib.h>

typedef struct Array{
	int *base,
			*dp;
} Array;

int upbound_bsearch(const int *a, int size, const int num){
	size--;
	int l = 0, id, cur_dif, min_dif = a[size] - num, res_id=-1;

	while(l <= size){
		id = (size + l) / 2;
		if(a[id] > num){
			size = id - 1;
		}
		else{
			l = id + 1;
		}
		cur_dif = a[id] - num;
		if(cur_dif > 0 && cur_dif <= min_dif){
			min_dif = cur_dif;
			res_id = id;
		}
	}
	return res_id;
}

int main(){
	FILE *fi = fopen("input.txt", "r"),
			*fo = fopen("output.txt", "w");
	int N;                                                                                          //Initial array length
	fscanf(fi, "%d", &N);

	Array a;
	a.base = malloc(N * sizeof(int));                                                               //Initial array
	//dp[i] contains the index of the smallest element on which a subset of length i+1 can end
	a.dp = malloc(N * sizeof(int));
	for(int i = 0; i < N; i++) {
		fscanf(fi, "%d", &(a.base[i]));                                                             //read element value
		a.dp[i] = -1;
	}
	for(int step = 0; step < N; step++) {

	}

	fclose(fi);
	fclose(fo);
	return 0;
}