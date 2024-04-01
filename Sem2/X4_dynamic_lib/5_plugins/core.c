#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dll_export.h"
typedef struct State {
    char *regs[256];
} State;

MYDLL_API void echo_0(State *state){
    printf("ECHO: \n");
    fflush(stdout);
}

MYDLL_API void echo_1(State *state, char *arg0){
    printf("ECHO: %s\n", arg0);
    fflush(stdout);
}
MYDLL_API void echo_2(State *state, char *arg0, char *arg1){
    printf("ECHO: %s|%s\n", arg0, arg1);
    fflush(stdout);
}
MYDLL_API void echo_3(State *state, char *arg0, char *arg1, char *arg2){
    printf("ECHO: %s|%s|%s\n", arg0, arg1, arg2);
    fflush(stdout);
}

MYDLL_API void print_1(State *state, char *idx){
    int dec_idx = atoi(idx);

    if(state->regs[dec_idx] != NULL){
        printf("%s\n", state->regs[dec_idx]);
        fflush(stdout);
    }
}

MYDLL_API void printregs_0(State *state){
    for (int i = 0; i < 256; i++) {
        if(state->regs[i] != NULL){
            printf("%d = %s\n", i, state->regs[i]);
        }
    }
    fflush(stdout);
}

MYDLL_API void store_2(State *state, char *idx, char *what){
    int dec_idx = atoi(idx);

    if(state->regs[dec_idx] != NULL){
        free(state->regs[dec_idx]);
    }

    state->regs[dec_idx] = malloc(strlen(what) + 1);
    strcpy(state->regs[dec_idx], what);
}

MYDLL_API void copy_2(State *state, char *dst, char *src){
    int dec_dst = atoi(dst);
    int dec_src = atoi(src);

    if(dec_dst == dec_src || state->regs[dec_src] == NULL)
        return;

    if(state->regs[dec_dst] != NULL){
        free(state->regs[dec_dst]);
    }
    state->regs[dec_dst] = malloc(strlen(state->regs[dec_src]) + 1);
    strcpy(state->regs[dec_dst], state->regs[dec_src]);
}

MYDLL_API void clear_1(State *state, char *idx){
    int dec_idx = atoi(idx);

    if(state->regs[dec_idx] != NULL){
        free(state->regs[dec_idx]);
    }
    state->regs[dec_idx] = NULL;
}