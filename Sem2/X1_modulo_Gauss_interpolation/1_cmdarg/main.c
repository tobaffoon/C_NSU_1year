#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//evaluates an expression consisting of one op and two operands
long long evaluate(char* op, int number1, int number2){
    long long result;

    //addition
    if(strcmp(op, "add") == 0)
        result = (long long)number1 + (long long)number2;

    //subtraction
    else if(strcmp(op, "sub") == 0)
        result = (long long)number1 - (long long)number2;

    //multiplication
    else if(strcmp(op, "mul") == 0)
        result = (long long)number1 * (long long)number2;

    //something is wrong
    else
        return 0xFFFFFFFFFFFFFFFF;

    return result;
}

//signed module
long long smod(long long number, int module){
    long long result = number % module;
    if(result < 0)
        result += module;
    return result;
}

int main(int argc, char **argv) {

    //if not enough parameters are passed
    if(argc < 4){
        fprintf_s(stderr, "No parameters specified.");
        return 13;
    }

    long long return_value;                //the result
    char operation[3];                     //the string containing name of the operation
    int operand1, operand2;

    //if module is passed
    if(argc == 6){
        int module;

        //if module is passed first
        if(strcmp(argv[1], "-m") == 0){
            module = atoi(argv[2]);
            strcpy(operation, argv[3]);
            operand1 = atoi(argv[4]);
            operand2 = atoi(argv[5]);
        }

        //if operation is passed first
        else{
            module = atoi(argv[5]);
            strcpy(operation, argv[1]);
            operand1 = atoi(argv[2]);
            operand2 = atoi(argv[3]);
        }

        return_value = smod(
                evaluate(operation, operand1, operand2), module);

        fprintf_s(stdout, "%lld", return_value);
    }

    //if module is not passed
    else{
        strcpy(operation, argv[1]);
        operand1 = atoi(argv[2]);
        operand2 = atoi(argv[3]);

        return_value = evaluate(operation, operand1, operand2);
        fprintf_s(stdout, "%lld", return_value);
    }
    return 0;
}
