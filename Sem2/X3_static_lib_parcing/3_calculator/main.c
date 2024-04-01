#include <stdio.h>

#define IS_DIGIT(c) ((c) >= '0' && (c) <= '9')
#define NUM(c) ((c) - '0')

double parse_atom();
double parse_monome();
double parse_expr();

char text[500000];
int ptr = 0;

char read_token(){
    while (text[ptr] == ' ')
        ptr++;

    if (text[ptr] == 0)
        return EOF;

    return text[ptr++];
}

char peek_token(){
    int beg = ptr;
    char res = read_token();
    ptr = beg;
    return res;
}

double get_dbl(){
    double res = NUM(read_token());


    while(IS_DIGIT(peek_token())){
        res = res * 10 + NUM(read_token());
    }

    return res;
}

double parse_atom(){
    if(peek_token() == '-'){
        read_token();           //skip '-'
        return (-1) * parse_atom();
    }
    if(peek_token() == '(') {
        read_token();   //skip '('
        double res = parse_expr();
        read_token();   //skip ')'
        return res;
    }
    else{
        return get_dbl();
    }
}

double parse_monome(){
    double  res = parse_atom(),
            snd_arg;
    char op;

    while(peek_token() == '*' || peek_token() == '/'){
        op = read_token();
        snd_arg = parse_atom();

        if(op == '*')
            res *= snd_arg;
        else
            res /= snd_arg;
    }
    return res;
}

double parse_expr(){
    double  res = parse_monome(),
            snd_arg;
    char op;

    while(peek_token() == '+' || peek_token() == '-'){
        op = read_token();
        snd_arg = parse_monome();

        if(op == '+')
            res += snd_arg;
        else
            res -= snd_arg;
    }
    return res;
}

int main() {
    FILE    *fi = fopen("input.txt", "r"),
            *fo = fopen("output.txt", "w");

    fgets(text, 500000, fi);

    fprintf_s(fo, "%.20lf", parse_expr());

    fclose(fi);
    fclose(fo);
    return 0;
}
