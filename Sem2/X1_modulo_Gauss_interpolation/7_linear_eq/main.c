#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STEPPED_MATRIX 1
#define ZERO_COLUMN 0

//returns address of new allocated table of doubles
double **malloc_double_table(int count){
    double **address = malloc(sizeof(double *) * count);
    for (int i = 0; i < count; i++) {
        address[i] = malloc(sizeof(double) * (count + 1));
    }

    return address;
}

//frees square table of doubles with 'size' rows
void free_double_table(double ***table, int size){
    for (int i = 0; i < size; i++) {
        free((*table)[i]);
    }
    free(*table);
}

//returns second line with zeroed first element
void nullify_first_var(const double *first_line, double *second_line, int length){
    double multiplier = (*second_line) / (*first_line);

    if(multiplier == 0)
        return;

    //<= length because b_i won't be counted otherwise
    for (int i = 0; i <= length; i++) {
        second_line[i] -= first_line[i] * multiplier;
    }
}

//swaps two arrays of doubles
void swap_lines(double ***src, int length, int first_line, int second_line){
    double *temp = malloc((length + 1) * sizeof(double));

    memcpy(temp, (*src)[first_line], (length + 1) * sizeof(double));
    memcpy((*src)[first_line], (*src)[second_line], (length + 1) * sizeof(double));
    memcpy((*src)[second_line], temp, (length + 1) * sizeof(double));

    free(temp);
}

//tries to swap rows in matrix to make var_(var_number) not null
int turn_stepped(double ***matrix, int var_number, int length){
    int row = var_number;                                                                                               //start checking from the row which already has var_number leading null coefficients
                                                                                                                        //if we choose upper rows we wouldn't be able to make stepped matrix
    while(row < length && (*matrix)[row][var_number] == 0){
        row++;
    }

    if(row == length){
        return ZERO_COLUMN;
    }

    if(row != 0)                                                                                                        //if matrix is stepped no need to swap lines
        swap_lines(matrix, length, row, var_number);

    return STEPPED_MATRIX;
}

//returns array of roots od system presented as stepped matrix
double *restore_solutions(double **equasions, int size){
    double *result = calloc(size, sizeof(double));

    for (int i = size-1; i >= 0; i--) {                                                                                 //0*x0 + 0*x1 + ... + an*xn + a(n+1)*x(n+1) + ... + a_(size-1)*x_(size-1) = bn
        for (int j = size - 1; j > i; j--) {
            equasions[i][size] -= equasions[i][j] * result[j];                                                          //an*xn = bn - (a(n+1)*x(n+1) + ... + a_(size-1)*x_(size-1)) = Bn
        }
        result[i] = equasions[i][size] / equasions[i][i];                                                               //xn = Bn/an
    }

    return result;
}

//prints arrays of doubles in output
void fprint_double_arr(FILE *output, double *src, int size){
    for (int i = 0; i < size; i++) {
        fprintf_s(output, "%lf\n", src[i]);
    }
}

int main() {
    FILE    *fi = fopen("input.txt", "r"),
            *fo = fopen("output.txt", "w");

    int dimension,                                                                                                      //dim A, where A is matrix corresponding to the polynomials
        stepped_result;                                                                                                 //flag to know if making matrix stepped was successful

    fscanf(fi, "%d", &dimension);

    double **equasions = malloc_double_table(dimension),                                                                //arrays of n polynomials of size n + 1 number for the values of polynomials
            *solutions;                                                                                                 //array of values pf variables

    for (int i = 0; i < dimension; i++) {
        for (int j = 0; j <= dimension; j++) {
            fscanf(fi, "%lf", equasions[i] + j);
        }
    }

    int last_var = dimension - 1;

    for (int i = 0; i < last_var; i++) {
        stepped_result = turn_stepped(&equasions, i, dimension);                                                        //if possible make var number i not zero

        if(stepped_result == ZERO_COLUMN)                                                                               //if it's impossible neglect the column
            continue;

        for (int j = i+1; j < dimension; j++) {
            nullify_first_var(equasions[i] + i, equasions[j] + i, dimension - i);              //+i because previous vars are zero, so no need to change them
        }
    }

    solutions = restore_solutions(equasions, dimension);

    fprint_double_arr(fo, solutions, dimension);

    free(solutions);
    free_double_table(&equasions, dimension);
    fclose(fi);
    fclose(fo);
    return 0;
}