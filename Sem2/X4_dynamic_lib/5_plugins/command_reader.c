#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct String{
    char *str;
    int len;
} String;
typedef struct Command {
    char plugin[40],
            function[40];
    int args_num;
    char args[4][350];
} Command;

int parseArgs(Command *command){
    int count = 0;
    String hArg;
    hArg.str = malloc(256);

    char    hChar;
    int     scan_status;
    scan_status = scanf("%c", &hChar);

    while (hChar != '\n' && scan_status != EOF) {
        hArg.len = 0;

        //pass extra white spaces
        while (hChar == ' ')
            scan_status = scanf("%c", &hChar);

        //read and store the argument in buffer
        while (hChar != ' ' && hChar != '\n' && scan_status != EOF) {
            hArg.str[hArg.len++] = (char) hChar;
            scan_status = scanf("%c", &hChar);
        }
        hArg.str[hArg.len++] = '\0';

        memcpy(command->args[count], hArg.str, hArg.len);
        count++;
    }
    command->args_num = count;

    free(hArg.str);

    //we return EOF or last character read
    if(scan_status != EOF)
        scan_status = (int)hChar;

    return scan_status;
}

//parses plugin (-> regs[0]) and function (-> regs[1]) names
//returns 1 if there are arguments (line hasn't ended)
//returns 0 otherwise
int parseInst(Command *command){
    String     hWord;      //both str and len are considering '\0'

    hWord.str = malloc(31);                        //first word is either a plugin or a function name
    hWord.len = 0;

    char hChar;
    int  scan_status;
    scan_status = scanf("%c", &hChar);

    while(hChar != ' ' && hChar != ':' && hChar != '\n' && scan_status != EOF){       //while the input is not over, or we reached the second word (they are divided with :)
//        if(hChar != '\r')
            hWord.str[hWord.len++] = hChar;
        scan_status = scanf("%c", &hChar);
    }

    hWord.str[hWord.len++] = '\0';

    //hWord is the plugin name
    if(hChar == ':'){
        memcpy(command->plugin, hWord.str, hWord.len);

        //now read the function name
        hWord.len = 0;
        scan_status = scanf("%c", &hChar);
        while(hChar != ' ' && hChar != '\n' && scan_status != EOF){
//            if(hChar != '\r')
                hWord.str[hWord.len++] = hChar;
            scan_status = scanf("%c", &hChar);
        }

        hWord.str[hWord.len++] = '\0';

        memcpy(command->function, hWord.str, hWord.len);
    }

        //hWord is a function name
    else {
        memcpy(command->plugin, "core", 5);                          //default plugin is core
        memcpy(command->function, hWord.str, hWord.len);
    }

    free(hWord.str);

    //we return EOF or last character read
    if(scan_status != EOF)
        scan_status = (int)hChar;

    return scan_status;
}

int parseCommand(Command *command){
    int scan_status = parseInst(command);

    if(scan_status != '\n' && scan_status != EOF) {
        scan_status = parseArgs(command);
    }
    else{
        command->args_num = 0;
    }

    return scan_status;
}