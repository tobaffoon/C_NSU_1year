#include <stdlib.h>
#include <string.h>
typedef struct State {
    char *regs[256];
} State;

__declspec(dllexport) void concat_2(State *state, char *idx0, char *idx1){
    int dec_dst = atoi(idx0);
    int dec_src = atoi(idx1);

    if(state->regs[dec_src] == NULL)
        return;

    size_t newLen = strlen(state->regs[dec_dst]) + strlen(state->regs[dec_src]) + 1;

    char *buf = malloc(newLen);
    strcpy(buf, state->regs[dec_dst]);
    strcat(buf, state->regs[dec_src]);

    if(state->regs[dec_dst] != NULL){
        free(state->regs[dec_dst]);
    }
    state->regs[dec_dst] = malloc(newLen);

    strcpy(state->regs[dec_dst], buf);

    free(buf);
}

//extracts sequence of tokens/words separated by underscore character from string [arg]
//puts K –- number of tokens into 0-th register
//puts the tokens into 1-th, 2-th, ..., K-th registers (in correct order)
__declspec(dllexport) void tokenize_1(State *state, const char *arg){
    int reg_num = 1,        //current write-in register's id
        pos = 0,            //current position in arg
        res_pos;

    //search for the arguments to the end of line
    while(arg[pos] != '\n' && arg[pos] != '\r' && arg[pos] != '\0'){
        res_pos = 0;
        //search the beginning of the next argument
        while(arg[pos] == '_'){
            pos++;
        }

        if(arg[pos] == '\n' || arg[pos] == '\r' || arg[pos] == '\0'){
            break;
        }

        if(state->regs[reg_num] != NULL){
            free(state->regs[reg_num]);
        }
        state->regs[reg_num] = malloc(256);

        //search the end of the current argument or the end of the line
        while(arg[pos] != '_' && arg[pos] != '\n' && arg[pos] != '\r' && arg[pos] != '\0'){
            state->regs[reg_num][res_pos++] = arg[pos++];
        }

        state->regs[reg_num][res_pos] = '\0';

        reg_num++;
    }

    if(state->regs[0] != NULL){
        free(state->regs[0]);
    }
    state->regs[0] = malloc(18);

    //store number of arguments in the first register
    itoa(reg_num - 1, state->regs[0], 10);
}
