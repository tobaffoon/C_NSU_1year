#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Command {
    char    *plugin,
            *function;
    int     plugin_length,
            function_length;
    int args_num;
    char args[3][1000];
} Command;

//separates function and plugin names, also counts their length
void dividePlugin(Command *command) {
    sscanf(command->function, "%[^:]%n", command->plugin, &(command->plugin_length));

    //if there was no plugin name, lengths are equal (we scanned until '\0')
    if (command->plugin_length == command->function_length) {
        memcpy(command->plugin, "core", 5);
        command->plugin_length = 4;
    } else {
        //move pointers to not copy the string
        command->function += command->plugin_length + 1;
        command->function_length -= command->plugin_length + 1;
    }
}
/*void dividePlugin(Command *command) {
    int pos = 0;
    while (command->function[pos] != ':') {
        if (command->function[pos] == '\0') {
            memcpy(command->plugin, "core", 5);
            return;
        }
        pos++;
    }

    command->function[pos] = '\0';
    strcpy(command->plugin,
           command->function);
    command->function += pos + 1;
}*/

//stores plugin and function names, arguments and their number in command
//returns 1 or 0 if there may be lines left
//returns (-1) if the end of the file was reached
int readCommandL(Command *command) {
    command->args_num = 0;
    scanf("%*[ \n]");
    scanf("%s%n", command->function, &(command->function_length));

    int field_filled = scanf("%*[ ]%[^\n ]", command->args[0]);
    while(field_filled != 0 && field_filled != EOF){
        field_filled = scanf("%*[ ]%[^\n ]", command->args[++command->args_num]);
    }
    if(field_filled != EOF) {
        command->plugin_length = 0;
        dividePlugin(command);
    }

    return field_filled;
}