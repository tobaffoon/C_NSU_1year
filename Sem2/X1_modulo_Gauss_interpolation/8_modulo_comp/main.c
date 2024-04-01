#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#define STEPPED_MATRIX 1
#define ZERO_COLUMN 0
#define NO_SOLUTIONS -1
#define SOLUTIONS_MOD 1000000007

#define MAX(A,B) (((A) > (B)) ? (A) : (B))

///calculates 'base' in the power 'exponent' in modulo 'module'
uint64_t fast_pow(uint64_t base, int exponent, int module){
    uint64_t      result = 1,                     //current value
    current_power = base % module;  //base raised to current power of two

    while(exponent != 0){               //we set bits of exponent zero one by one and when it becomes zero, we halt
        if((exponent & 1) != 0) {    //if mask (= 2^n, where n is the number of current iteration) is present in decomposition to powers of two of exponent
            result *= current_power;    //we include base^(2^n) in the result
            result %= module;
        }
        exponent >>= 1;              //now we don't need this bit
        current_power *= current_power; //next power = (current power) ^ 2
        current_power %= module;
    }

    return result;
}

///returns address of new allocated table of doubles
uint64_t **malloc_equasions_table(int rows, int vars){
    uint64_t **address = malloc(sizeof(uint64_t *) * rows);                                                        //allocate rows

    for (int i = 0; i < rows; i++) {
        address[i] = malloc(sizeof(uint64_t) * (vars + 1));                                                        //allocate vars
    }

    return address;
}

///frees square table of doubles with 'size' rows
void free_equasions_table(uint64_t ***table, uint64_t size){
    for (int i = 0; i < size; i++) {
        free((*table)[i]);                                                                                              //free vars
    }
    free(*table);                                                                                                       //free rows
}

///returns second line with zeroed first element
void nullify_first_var(const uint64_t *first_line, uint64_t *second_line, int length, int module){
    uint64_t multiplier = ((*second_line) * (fast_pow(*first_line, module - 2, module))) % module;             //second_line[0] - (multiplier * first_line[0])

    if(multiplier == 0)
        return;

    for (int i = 0; i <= length; i++) {
        second_line[i] = (second_line[i] - (first_line[i] * multiplier) % module + module) % module;                    //y_i = y_i - x_i * multiplier
    }
}

///swaps two arrays of uints
void swap_lines(uint64_t ***src, int length, int first_line, int second_line){
    uint64_t *temp = malloc((length + 1) * sizeof(uint64_t));                                                     //buffer

    memcpy(temp, (*src)[first_line], (length + 1) * sizeof(uint64_t));                                            //first => temp
    memcpy((*src)[first_line], (*src)[second_line], (length + 1) * sizeof(uint64_t));                             //second => first
    memcpy((*src)[second_line], temp, (length + 1) * sizeof(uint64_t));                                           //temp(first) => second

    free(temp);
}

///tries to swap rows in matrix to make var_(var_idx) not null
int turn_stepped(uint64_t ***matrix, int cur_row, int var_idx, int vars, int rows){
    int new_row = cur_row;                                                                                              //row with non-zero var

    //first condition is to find full-zero columns
    //second condition is to find non-zero row
    while(new_row < rows && (*matrix)[new_row][var_idx] == 0){
        new_row++;
    }

    if(new_row == rows)
        return ZERO_COLUMN;

    if(new_row != cur_row)                                                                                              //if matrix is stepped no need to swap lines
        swap_lines(matrix, vars, cur_row, new_row);

    return STEPPED_MATRIX;
}

///tries to make matrix diagonalised
int diag_matrix(uint64_t ***matrix, int vars, int rows, int mod) {
    int    extra_cols = vars - rows,                                                                                    //number of free vars
                stepped_result,                                                                                         //flag to check if all coefs with cur_var are zero
                zero_cols = 0,                                                                                          //number of zero columns
                cur_row = 0,                                                                                            //idx of current row
                tempv = vars - 1;                                                                                       //used for 'for cycle'

    for (int i = 0; i < tempv; i++) {                                                                                   //i is var's idx
        stepped_result = turn_stepped(matrix, cur_row, i, vars, rows);                                                  //if possible make var number i not zero

        if(stepped_result == ZERO_COLUMN) {                                                                             //if it's impossible neglect the column
            zero_cols++;
            continue;
        }

        for (int j = cur_row+1; j < rows; j++) {                                                                        //subtract first line from all the lines below
            nullify_first_var((*matrix)[cur_row] + i, (*matrix)[j] + i, vars - i, mod);        //+i because previous vars are zero, so no need to change them
        }

        cur_row++;
    }

    //if there are more rows - nullify them (happens when there are more rows than vars)
    if(cur_row < rows - 1){
        stepped_result = turn_stepped(matrix, cur_row, vars - 1, vars, rows);

        if(stepped_result == ZERO_COLUMN) {
            zero_cols++;
        }

        for (int j = cur_row+1; j < rows; j++) {
            nullify_first_var((*matrix)[cur_row] + vars - 1, (*matrix)[j] + vars - 1, 1, mod);
        }

    }

    return MAX(extra_cols, zero_cols);                                                                                  //extra_cols may be zero_cols
}

///returns number of possible new free vars = "trivial lines"
int trivial_lines_num(uint64_t **matrix, int vars, int rows){
    int    tr_lines = 0;                                                                                                //number of lines with all zeroes
    int    null_coefs;                                                                                                  //flag to see if coefficients in equation are zero (1 - TRUE, 0 - FALSE)

    for (int i = 0; i < rows; ++i) {
        null_coefs = 1;
        for (int j = 0; j < vars; j++) {
            if(matrix[i][j] != 0) {                                                                                     //checks if all this var's coefficients are zero
                null_coefs = 0;
                break;
            }
        }

        if(null_coefs == 1){
            if(matrix[i][vars] == 0)                                                                                    //all zeroes
                tr_lines++;
            else                                                                                                        //sum of zeroes equals not zero
                return NO_SOLUTIONS;
        }
    }

    return tr_lines;
}

///returns array of roots od system presented as stepped matrix
uint64_t *restore_solutions(uint64_t ***matrix, int vars, int rows, int module){
    uint64_t *result = calloc(vars, sizeof(uint64_t));
    int last_var = vars - 1,                                                                                            //-> last var
        cur_var,
        cur_row;

    for (int i = 0; i < rows; i++) {                                                                                    //0*x0 + 0*x1 + ... + an*xn + a(n+1)*x(n+1) + ... + a_(vars-1)*x_(vars-1) = bn
        cur_var = last_var - i,                                                                                         //vars - 1 = last var, last var - i = current var, current var - 1 = it's index counting from 0
        cur_row = rows - 1 - i;                                                                                         //rows - 1 = last row, last row - i = current row

        while((*matrix)[cur_row][cur_var] == 0){
            cur_var--;                                                                                                  //we might have some zero columns, but yet solvable system
        }

        for (int j = cur_var + 1; j < vars; j++) {
            if((*matrix)[cur_row][j] != 0) {
                //an*xn = bn - (a(n+1)*x(n+1) + ... + a_(vars-1)*x_(vars-1)) = Bn
                (*matrix)[cur_row][vars] = ((*matrix)[cur_row][vars] - ((*matrix)[cur_row][j] * result[j] % module) + module) % module;
            }
        }

        //xn = Bn / an
        result[cur_var] = (((*matrix)[cur_row][vars] * fast_pow((*matrix)[cur_row][cur_var], module - 2, module)) % module + module) % module;                                                                                               //xn = Bn/an
    }

    return result;
}

///prints arrays of doubles in output
void fprint_line(FILE *output, uint64_t *src, int size){
    for (int i = 0; i < size; i++) {
        fprintf_s(output, "%llu\n", src[i]);
    }
}

int main() {
    FILE    *fi = fopen("input.txt", "r"),
            *fo = fopen("output.txt", "w");

    int num_of_rows,
        num_of_vars,
        system_module,
        num_of_free_var;                                                                                                //number of lines that can be turned zero with diagonalising. We need it to check if zero coefficients. dimA - rgA
                                                                                                                        //mean zero right part (if not => zero is no solution)

    fscanf(fi, "%d%d%d", &num_of_vars, &num_of_rows, &system_module);

    uint64_t    **equasions = malloc_equasions_table(num_of_rows, num_of_vars);                                         //arrays of n polynomials of size n + 1 number for the values of polynomials

///read matrix
    for (int i = 0; i < num_of_rows; i++) {
        for (int j = 0; j <= num_of_vars; j++) {
            fscanf(fi, "%llu", equasions[i] + j);
        }
    }

///diagonalise matrix
    num_of_free_var = diag_matrix(&equasions, num_of_vars, num_of_rows, system_module);

    int num_of_depend_var = num_of_vars - num_of_free_var;                                                              //current number of meaningful vars

    //check if there are zero lines: if right part is zero, then there are multiple solutions, else there is none
    int tr_lines = trivial_lines_num(equasions, num_of_vars, num_of_rows);                                              //lines with zero coefs
    int proper_lines = num_of_rows - tr_lines;                                                                          //number of meaningful equations

    if(tr_lines == NO_SOLUTIONS)
        fprintf_s(fo, "0\n");

    else{
        if(num_of_depend_var > proper_lines)                                                                            //if there are not enough equations to solve the system, some vars must be free
            num_of_free_var += tr_lines;

        uint64_t num_of_solutions = fast_pow(system_module, num_of_free_var, SOLUTIONS_MOD);                            //each free var may be from (0; module-1) => module*module*...*module = module^free_var solutions

        fprintf_s(fo, "%llu\n", num_of_solutions);

        if(num_of_solutions == 1) {
            uint64_t *solutions;                                                                                        //array of values pf variables

            solutions = restore_solutions(&equasions, num_of_vars, proper_lines, system_module);

            fprint_line(fo, solutions, num_of_depend_var);

            free(solutions);
        }
    }

    free_equasions_table(&equasions, num_of_rows);
    fclose(fi);
    fclose(fo);
    return 0;
}