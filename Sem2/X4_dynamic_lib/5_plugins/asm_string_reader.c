#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Command {
    char plugin[40],
            function[40];
    int args_num;
    char args[4][350];
} Command;

static char* line;

//returns last character read
char readToken(char *token) {
    char scanned = (char)sscanf(line, "%s", token);
    if(scanned != EOF) {
        line += strlen(token);
        while (line[0] == ' ') {
            line++;
        }
    }
    return scanned;
}

//looks for found_c in str
//returns its position if str contains it
//return -1 if str doesn't
int strfind(const char *str, const char found_c) {
    if (str == NULL)
        return -1;
    int find_pos = 0;

    while (str[find_pos] != found_c && str[find_pos] != '\0') {
        find_pos++;
    }

    //if we found needed \0 or other needed symbol
    if (found_c == '\0' || str[find_pos] != '\0')
        return find_pos;

    //if we didn't find the symbol
    return -1;
}

//stores a word in str is possible
//returns 1 if it could read a word
//returns 0 if no words could have been read until the end of line
void getArgs(Command *command) {
    char temp[350];
    char scanned = readToken(temp);

    while(scanned != 0 && scanned != EOF){
        memcpy(command->args[command->args_num++], temp, strlen(temp) + 1);
        scanned = readToken(temp);
    }
}

void readPluginFunction(Command *command) {
    char temp[70];
    char scanned = readToken(temp);

    if (scanned != 0 && scanned != EOF) {

        int plugin_name_length = strfind(temp,
                                         ':');  //index of dividing plugin and function names (i.e. plugin's length - 1)
        if (plugin_name_length == -1) {
            memcpy(command->plugin, "core", 5);
            memcpy(command->function, temp, strlen(temp) + 1);
        } else {
            memcpy(command->plugin, temp, plugin_name_length);
            command->plugin[plugin_name_length] = '\0';

            memcpy(command->function, temp + plugin_name_length + 1,
                   strlen(temp) - plugin_name_length);
        }
    }
}

//stores plugin and function names, arguments and their number in command
//returns 1 or 0 if there may be lines left
//returns (-1) if the end of the file was reached
void* readCommandS(Command *command) {
    line = malloc(1011);
    char *for_free = line;
    void* scan_status = (void *)gets(line);

    if(scan_status != NULL) {
        command->args_num = 0;
        command->plugin[0] = '\0';
        command->function[0] = '\0';
//        readPluginFunction(command);
//        getArgs(command);
        int scanned = sscanf(line, "%s %s %s %s", command->plugin, command->args[0], command->args[1], command->args[2]);
        command->args_num = scanned - 1;
    }

    free(for_free);
    return scan_status;
}