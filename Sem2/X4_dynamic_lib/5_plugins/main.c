#include <stdlib.h>
#include <stdio.h>
//#include <time.h>
#include <windows.h>
typedef struct State {
    char *regs[256];
} State;
typedef struct Command {
    char    *plugin,
            *function;
    int     plugin_length,
            function_length;
    int args_num;
    char args[3][1000];
} Command;

typedef void (*dllFunction_0)(State *);
typedef void (*dllFunction_1)(State *, char*);
typedef void (*dllFunction_2)(State *, char*, char*);
typedef void (*dllFunction_3)(State *, char*, char*, char*);

//char readCommand(Command *command);
//void* readCommandS(Command *command);
int readCommandL(Command *command);
//char* readCommandL(Command *command);
//int parseCommand(Command *command);
State state;
Command command;

void executeFunction(void* myfunc){
    if(command.args_num == 0){
        ((dllFunction_0)myfunc)(&state);
    }
    else if(command.args_num == 1){
        ((dllFunction_1)myfunc)(&state, command.args[0]);
    }
    else if(command.args_num == 2){
        ((dllFunction_2)myfunc)(&state, command.args[0], command.args[1]);
    }
    else if(command.args_num == 3){
        ((dllFunction_3)myfunc)(&state, command.args[0], command.args[1], command.args[2]);
    }
}

int main() {
//    freopen("input.txt", "r", stdin);
//    freopen("output.txt", "w", stdout);
//    clock_t start = clock();
    int scan_status;
    char* free_function;
    command.plugin = malloc(80);

    while (1) {
        command.function = malloc(80);      //80 because function initially may contain both function and plugin names
        free_function = command.function;

        scan_status = readCommandL(&command);
        if(scan_status == EOF) {
            free(free_function);
            break;
        }

        command.plugin[command.plugin_length] = '.';
        command.plugin[command.plugin_length+1] = 'd';
        command.plugin[command.plugin_length+2] = 'l';
        command.plugin[command.plugin_length+3] = 'l';
        command.plugin[command.plugin_length+4] = '\0';
//        strcat(dll_name, ".dll");              //make a dll plugin name

        HMODULE hDll = LoadLibrary(command.plugin);
        command.plugin[command.plugin_length] = '\0';   //return to just plugin name
        if(hDll == NULL){
            printf("Missing plugin %s\n", command.plugin);
            free(free_function);
            continue;
        }

        //strcat takes time, so we just keep the length of a string
        if(command.args_num == 0){
//            strcat(command.function, "_0");
            command.function[command.function_length] = '_';
            command.function[command.function_length+1] = '0';
            command.function[command.function_length+2] = '\0';
        }
        else if(command.args_num == 1){
//            strcat(command.function, "_1");
            command.function[command.function_length] = '_';
            command.function[command.function_length+1] = '1';
            command.function[command.function_length+2] = '\0';
        }
        else if(command.args_num == 2){
//            strcat(command.function, "_2");
            command.function[command.function_length] = '_';
            command.function[command.function_length+1] = '2';
            command.function[command.function_length+2] = '\0';
        }
        else if(command.args_num == 3){
//            strcat(command.function, "_3");
            command.function[command.function_length] = '_';
            command.function[command.function_length+1] = '3';
            command.function[command.function_length+2] = '\0';
        }

        void *myDllFunc = NULL;
        if(command.args_num == 0){
            myDllFunc = (dllFunction_0)GetProcAddress(hDll, command.function);
        }
        else if(command.args_num == 1){
            myDllFunc = (dllFunction_1)GetProcAddress(hDll, command.function);
        }
        else if(command.args_num == 2){
            myDllFunc = (dllFunction_2)GetProcAddress(hDll, command.function);
        }
        else if(command.args_num == 3){
            myDllFunc = (dllFunction_3)GetProcAddress(hDll, command.function);
        }

        if(myDllFunc == NULL){
            printf("Missing function %s in plugin %s\n", command.function, command.plugin);
//            FreeLibrary(hDll);

            free(free_function);
            continue;
        }

        executeFunction(myDllFunc);

//        FreeLibrary(hDll);

        free(free_function);
    }

    free(command.plugin);

//    clock_t stop = clock();
//    double elapsed = (double) (stop - start) / CLOCKS_PER_SEC;
//    printf("\nTime elapsed: %.5f\n", elapsed);
    return 0;
}
