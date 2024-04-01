#include <stdio.h>
#include <stdlib.h>

//stores characters from src into parameter until it reaches the '"'
void read_until_quote(FILE *src, char *parameter){
    char current_character;
    int idx = 0;

    fscanf(src, "%c", &current_character);

    while(current_character != '"'){
        parameter[idx] = current_character;
        idx++;
        fscanf(src, "%c", &current_character);
    }

    //to know where did the word end
    parameter[idx] = '\0';
}

//stores characters from src into parameter until it reaches the ' ' or it is the end of line. Returns last read character
char read_until_blank(FILE *src, char *parameter){
    char    current_character;
    int     idx = 0;

    fscanf(src, "%c", &current_character);

    while(current_character != ' ' && current_character != '\n'){
        parameter[idx] = current_character;
        idx++;
        fscanf(src, "%c", &current_character);
    }

    parameter[idx] = '\0';

    return current_character;
}

//prints string from src in dest and wraps it in []
void print_buffer(FILE *dest, char* src){
    fprintf_s(dest, "[");

    fprintf_s(dest, "%s", src);

    fprintf_s(dest, "]\n");
}

int main() {
    FILE    *fi = fopen("input.txt", "r"),
            *fo = fopen("output.txt", "w");

    char    *buffer             = malloc(100);                                        //current word
    char    current_character;

    fscanf(fi, "%c", &current_character);

    while(current_character != '\n') {
        if (current_character != ' '){
            if (current_character == '"') {
                read_until_quote(fi, buffer);
            }

            else {
                *buffer = current_character;
                current_character = read_until_blank(fi, buffer + 1);
                if(current_character == '\n'){
                    print_buffer(fo, buffer);
                    break;
                }
            }
            print_buffer(fo, buffer);
        }

        fscanf(fi, "%c", &current_character);
    }

    fclose(fi);
    fclose(fo);
    return 0;
}
