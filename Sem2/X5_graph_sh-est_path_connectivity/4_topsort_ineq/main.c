#include <stdio.h>
#include <stdlib.h>

//growing array
typedef struct Smaller {
	int n,
			cap,
			*ns;
} Smaller;

enum Mark {
	black,
	grey,
	white,
};

typedef struct Variable {
	enum Mark mark;
	int color;
	Smaller ss; //smaller numbers
} Variable;

typedef struct Inequality {
	Variable *variables;
	int n_num;          //number of variables
} Inequality;

typedef struct Sorting {
	int *signifying;
	char is_Cycle;
	int DFS_tout;
} Sorting;

void DFS(Inequality *inequality, int start, int c, Sorting *array) {
	if(inequality->variables[start].mark != white) {
		return;
	}
	inequality->variables[start].mark = grey;
	inequality->variables[start].color = c;
	for(int i = 0; i < inequality->variables[start].ss.n; i++) {
		if(inequality->variables[inequality->variables[start].ss.ns[i]].mark == grey) {
			array->is_Cycle = 1;
			return;
		}
		inequality->variables[inequality->variables[start].ss.ns[i]].color = c;
		DFS(inequality, inequality->variables[start].ss.ns[i], c, array);
		//to pass is_Cycle through recursion
		if(array->is_Cycle == 1)
			return;
	}
	inequality->variables[start].mark = black;
//    array->ds[array->DFS_tout++] = start+1;
	array->signifying[start] = ++array->DFS_tout;
}

void TopSort(Inequality *inequality, Sorting *array) {
	int color = 1;
	for(int i = 0; i < inequality->n_num; i++) {
		DFS(inequality, i, color, array);
		if(array->is_Cycle) {
			return;
		}
		color++;
	}
}

void smaller_push(Smaller *ls, int num) {
	if(ls->cap == 0) {
		ls->cap = 2;
		ls->ns = malloc(sizeof(int) * ls->cap);
	}
	if(ls->n == ls->cap) {
		ls->cap *= 2;
		ls->ns = (int *) realloc(ls->ns, sizeof(int) * ls->cap);
	}
	ls->ns[ls->n++] = num;
}

void inequality_free(Inequality *inequality) {
	for(int i = 0; i < inequality->n_num; i++) {
		if(inequality->variables[i].ss.cap != 0) {
			free(inequality->variables[i].ss.ns);
		}
	}
	free(inequality->variables);
}

int main() {
	FILE *fi = fopen("input.txt", "r"),
			*fo = fopen("output.txt", "w");
	Inequality inequality;
	int expr_num;       //number if inequalities
	fscanf(fi, "%d %d", &(inequality.n_num), &expr_num);
	Sorting toposort;
	toposort.signifying = malloc(inequality.n_num * sizeof(int));
	toposort.DFS_tout = 0;
	toposort.is_Cycle = 0;
	inequality.variables = calloc(inequality.n_num, sizeof(Variable));
	for(int i = 0; i < inequality.n_num; i++) {
		inequality.variables[i].mark = white;
		inequality.variables[i].color = 0;
	}
	int small, big;
	for(int i = 0; i < expr_num; i++) {
		fscanf(fi, "%d %d", &small, &big);
		smaller_push(&(inequality.variables[big - 1].ss), small - 1);
	}
	TopSort(&inequality, &toposort);
	if(toposort.is_Cycle) {
		fprintf(fo, "NO");
	}
	else {
		fprintf(fo, "YES\n");
		for(int i = 0; i < inequality.n_num; i++) {
			fprintf(fo, "%d ", toposort.signifying[i]);
		}
	}
	inequality_free(&inequality);
	free(toposort.signifying);
	fclose(fi);
	fclose(fo);
	return 0;
}
