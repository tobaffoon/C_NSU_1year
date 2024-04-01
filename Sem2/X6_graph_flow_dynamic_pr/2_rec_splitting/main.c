#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define MOD 1000000007
#define MIN(A,B) ((A)<(B)?(A):(B))

uint64_t Rec(int sum, int last, int N, uint64_t *mem){
	if(mem[sum * N + (last - 1)] == -1){
		uint64_t res = 0;
		if (sum == N)
			res = 1;
		else {
			for (int x = 1; x <= MIN(last, N-sum); x++) {
				res += Rec(sum + x, x, N, mem);
				res %= MOD;
			}
		}
		mem[sum * N + (last - 1)] = res;
	}
	return mem[sum * N + (last - 1)];
}

int main(){
	FILE *fi = fopen("input.txt", "r"),
			*fo = fopen("output.txt", "w");
	int N;
	fscanf(fi, "%d", &N);

	uint64_t *mem = malloc((N + 1) * N * sizeof(uint64_t));
	for(int i = 0; i < N + 1; i++) {
		for(int j = 0; j < N; j++) {
			mem[i * N + j] = -1;
		}
	}
	fprintf(fo, "%llu", Rec(0, N, N, mem));

	free(mem);
	fclose(fi);
	fclose(fo);
	return 0;
}