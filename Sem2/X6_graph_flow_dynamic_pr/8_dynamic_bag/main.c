#include <stdio.h>
#include <stdlib.h>

#define MAX(A, B) ((A)>(B)?(A):B)

typedef struct Item {
	int weight,
			cost;
} Item;

typedef struct Vector {
	int n, cap;
	int *arr;
} Vector;

void Vector_push(Vector *vec, int x) {
	if(vec->cap == 0) {
		vec->cap = 2;
		vec->arr = malloc(vec->cap * sizeof(int));
	}
	else if(vec->n == vec->cap) {
		vec->cap *= 2;
		vec->arr = realloc(vec->arr, vec->cap * sizeof(int));
	}
	vec->arr[vec->n++] = x;
}

int main() {
	FILE *fi = fopen("input.txt", "r"),
			*fo = fopen("output.txt", "w");
	int N, sumWeight;
	fscanf(fi, "%d %d", &N, &sumWeight);
	Item *items = malloc(N * sizeof(Item));
	for(int i = 0; i < N; i++) {
		fscanf(fi, "%d %d", &(items[i].weight), &(items[i].cost));
	}
	int **dp = malloc((N + 1) * sizeof(int *));
	for(int i = 0; i <= N; i++) {
		dp[i] = calloc((sumWeight + 1), sizeof(int));
	}
	for(int curI = 1; curI <= N; curI++) {
		for(int curW = 1; curW <= sumWeight; curW++) {
			//if items inflicts overweight, we don't bring it
			if(curW < items[curI - 1].weight) {
				//but we bring all the items we chose without this one before
				dp[curI][curW] = dp[curI - 1][curW];
			}
				//if not we take the better variant: with or without this item
			else {
				dp[curI][curW] = MAX(dp[curI - 1][curW],
				                     dp[curI - 1][curW - items[curI - 1].weight] +
				                     items[curI - 1].cost);
			}
		}
	}
	Vector optimizedBag = {0,0,0};
	int leftWeight = sumWeight;
	for(int curI = N; curI > 0; curI--) {
		if(dp[curI][leftWeight] == 0){
			break;
		}
		if(dp[curI][leftWeight] != dp[curI - 1][leftWeight]) {
			leftWeight -= items[curI - 1].weight;
			Vector_push(&optimizedBag, curI);
		}
	}
	fprintf(fo, "%d %d %d\n", optimizedBag.n, sumWeight - leftWeight, dp[N][sumWeight]);
	for(int i = optimizedBag.n - 1; i >= 0; i--) {
		fprintf(fo, "%d ", optimizedBag.arr[i]);
	}
	if(optimizedBag.cap != 0){
		free(optimizedBag.arr);
	}
	fclose(fi);
	fclose(fo);
	return 0;
}