#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define MOD 1000000007

int main(){
	FILE *fi = fopen("input.txt", "r"),
			*fo = fopen("output.txt", "w");
	int N;
	fscanf(fi, "%d", &N);

	uint64_t *dp = malloc((N + 1) * N * sizeof(uint64_t));
	for(int i = 0; i < N; i++) {
		dp[N * N + i] = 1;
	}

	for(int i = 0; i < N; i++) {
		dp[i * N + 0] = 1;
	}

	for(int sum = N - 1; sum >= 0; sum--) {
		for(int last = 2; last <= N; last++) {
			dp[sum * N + (last - 1)] = dp[sum * N + (last - 2)];
			if(sum + last <= N){
				dp[sum * N + (last - 1)] += dp[(sum + last) * N + (last - 1)];
				dp[sum * N + (last - 1)] %= MOD;
			}
		}
	}
	fprintf(fo, "%llu", dp[N - 1]);

	fclose(fi);
	fclose(fo);
	return 0;
}