#include <stdio.h>
#include <string.h>
typedef struct Command{
    char    plugin[33],
            function[33];
    int args_num;
    char args[3][300];
} Command;
#define EOL 0

//looks for found_c in str
//returns its position if str contains it
//return -1 if str doesn't
int strfind(const char* str, const char found_c){
    if(str == NULL)
        return -1;

    int pos = 0;
    while(str[pos] != found_c && str[pos] != '\0'){
        pos++;
    }

    //if we found needed \0 or other needed symbol
    if(found_c == '\0' || str[pos] != '\0')
        return pos;

    //if we didn't find the symbol
    return -1;
}

//stores a word in str is possible
//returns 1 if it could read a word
//returns 0 if no words could have been read until the end of line
//return (-1) if
char getArg(char *str){
    char hChar;
    int scanStatus = scanf("%c", &hChar);

    while(hChar == ' ' && scanStatus != EOF){
        scanStatus = scanf("%c", &hChar);
    }

    if(scanStatus == EOF){
        return EOF;
    }

    if(hChar == '\n' || hChar == '\r'){
        return EOL;
    }

    int i = 0;
    str[i++] = hChar;
    scanStatus = scanf("%c", &hChar);
    while (hChar != '\n' && hChar != '\r' && scanStatus != EOF){
        str[i++] = hChar;
    }
    return 1;
}

//stores plugin and function names, arguments and their number in command
//returns 1 or 0 if there may be lines left
//returns (-1) if the end of the file was reached
char readCommand(Command *command){
    char hWord[70];                 //current word
    command->args_num = 0;

    scanf("%s", hWord);

    int plugin_name_length = strfind(hWord, ':');  //index of dividing plugin and function names (i.e. plugin's length - 1)
    if(plugin_name_length == -1){
        memcpy(command->plugin, "core", 5);
        memcpy(command->function, hWord, strlen(hWord) + 1);
    }
    else{
        memcpy(command->plugin, hWord, plugin_name_length);
        command->plugin[plugin_name_length] = '\0';

        memcpy(command->function, hWord + plugin_name_length + 1, strlen(hWord) - plugin_name_length);
    }

    char end = getArg(command->args[command->args_num]);
    while(end != EOL && end != EOF){
        command->args_num++;
        end = getArg(command->args[command->args_num]);
    }

    return end;
}