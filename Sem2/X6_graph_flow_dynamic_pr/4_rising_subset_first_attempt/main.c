#include <stdio.h>
#include <stdlib.h>

unsigned long long mem=0;

typedef struct Vector{
	int n, cap;
	int *arr;
} Vector;

typedef struct Pair{
	int num, id;
} Pair;

int pair_comp(const void *a, const void *b){
	return ((Pair *)a)->num - ((Pair *)b)->num;
}

void vec_push(Vector *vec, int x){
	if(vec->cap == 0){
		vec->cap = 2;
		vec->arr = malloc(vec->cap * sizeof(int));
//		mem+=vec->cap * sizeof(int);
	}
	if(vec->n == vec->cap){
		vec->cap *= 2;
//		void *temp = vec->arr;
		vec->arr = realloc(vec->arr, vec->cap * sizeof(int));
//		if(temp != vec->arr)
//			mem+=vec->cap * sizeof(int) / 2;
	}
	vec->arr[vec->n++] = x;
}

Vector Rec(int step, int last, Pair *a, int len, Vector *bests){
	last+=1;
	if(bests[step*len+last].arr == NULL) {
		if(step == len - 1) {
			if(a[step].id >= last) {
				vec_push(&(bests[step*len+last]), step);
			}
		}
		else {
			for(int offset = step; offset < len - 1; offset++) {
				if(a[offset].id >= last) {
					Vector res;
					res = Rec(offset + 1, a[offset].id, a, len, bests);
					vec_push(&res, offset);
					if(res.n > bests[step*len+last].n) {
						if(bests[step*len+last].cap != 0) {
//							mem-=bests[step*len+last].cap * sizeof(int);
							free(bests[step*len+last].arr);
						}
						bests[step*len+last].n = res.n;
						bests[step*len+last].cap = res.cap;
						bests[step*len+last].arr = res.arr;
					}
				}
			}
		}
	}
	return bests[step*len+last];
}

int main(){
	FILE *fi = fopen("input.txt", "r"),
			*fo = fopen("output.txt", "w");
	int N;
	fscanf(fi, "%d", &N);
	Pair *a = malloc(N * sizeof(Pair));
//	mem+=N * sizeof(Pair);
	for(int i = 0; i < N; i++) {
		fscanf(fi, "%d", &(a[i].num));
		a[i].id = i;
	}
	qsort((void *) a, N, sizeof(Pair), &pair_comp);

	Vector *bests = calloc(N * (N + 1), sizeof(Vector));
//	mem+=N * (N + 1) * sizeof(Vector);

	Vector res = Rec(0, -1, a, N, bests);
	fprintf(fo, "%d\n", res.n);
	for(int i = res.n - 1; i >= 0; i--) {
		fprintf(fo, "A[%d] = %d\n", a[res.arr[i]].id + 1, a[res.arr[i]].num);
	}

	free(res.arr);
	fclose(fi);
	fclose(fo);
	return 0;
}