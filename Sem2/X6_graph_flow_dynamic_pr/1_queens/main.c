#include <stdio.h>
#include <stdlib.h>

void Place_queens(char **desk, int rows, int columns, int step, char *hasC, char *hasS, char *hasD, char *ans){
	if(step == rows){
		*ans = 1;
		return;
	}
	for(int i = 0; i < columns; i++) {
		if (desk[step][i] == '.' || hasC[i] || hasS[i + step] || hasD[i - step + rows - 1]){
			continue;
		}
		desk[step][i] = 'X';
		hasC[i] = 1;
		hasS[i + step] = 1;
		hasD[i - step + rows - 1] = 1;
		Place_queens(desk, rows, columns, step + 1, hasC, hasS, hasD, ans);
		if(*ans == 1){
			return;
		}
		desk[step][i] = '?';
		hasC[i] = 0;
		hasS[i + step] = 0;
		hasD[i - step + rows - 1] = 0;

	}
}

int main(){
	FILE *fi = fopen("input.txt", "r"),
			*fo = fopen("output.txt", "w");
	int n, m;
	fscanf(fi, "%d %d\n", &n, &m);
	char** desk = malloc(n * sizeof(char *));
	for(int i = 0; i < n; i++) {
		desk[i] = malloc(m);
		for(int j = 0; j < m; j++) {
			fscanf(fi, "%c", &(desk[i][j]));
		}
		fscanf(fi, "\n");
	}
	char *hasC = calloc(m, 1),
			*hasS = calloc(n + m - 1, 1),
			*hasD = calloc(n + m - 1, 1),
			ans = 0;
	Place_queens(desk, n, m, 0, hasC, hasS, hasD, &ans);
	if(ans == 0){
		fprintf(fo, "NO");
	}
	else{
		fprintf(fo, "YES\n");
		for(int i = 0; i < n; i++) {
			for(int j = 0; j < m; j++) {
				if(desk[i][j] == 'X'){
					fprintf(fo, "X");
				}
				else fprintf(fo, ".");
			}
			fprintf(fo, "\n");
		}
	}
	fclose(fi);
	fclose(fo);
	return 0;
}