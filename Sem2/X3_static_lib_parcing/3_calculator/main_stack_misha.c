#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>

#define open_bracket_priority 1
#define closing_bracket_priority 2
#define eq_priority 3
#define plus_priority 4
#define minus_priority 4
#define mult_priority 5
#define div_priority 5

typedef struct double_stack{
    double val;
    struct double_stack * next;
} double_stack;

typedef struct char_stack{
    char sign;
    int priority;
    struct char_stack * next;
} char_stack;

int is_empty_char(char_stack * stack)
{
    return (stack == NULL);
}

int is_empty_double(double_stack * stack)
{
    return (stack == NULL);
}

char get_char_elem(char_stack * stack)
{
    return stack->sign;
}

double get_double_elem(double_stack * stack)
{
    return stack->val;
}

int get_priority(char_stack * stack)
{
    return stack->priority;
}

char char_pop(char_stack ** stack)
{
    char res = (*stack)->sign;
    char_stack * a = (*stack);
    (*stack) = (*stack)->next;
    free(a);
    return res;
}

double double_pop(double_stack ** stack)
{
    double res = (*stack)->val;
    double_stack * a = (*stack);
    (*stack) = (*stack)->next;
    free(a);
    return res;
}

void char_push(char_stack ** stack, char val, int priority)
{
    char_stack * new = (char_stack *)malloc(sizeof(char_stack));
    new->sign = val;
    new->priority = priority;
    new->next = (*stack);
    (*stack) = new;
}

void double_push(double_stack ** stack, double val)
{
    double_stack * new = (double_stack *)malloc(sizeof(double_stack));
    new->val = val;
    new->next = (*stack);
    (*stack) = new;
}

void make_operation(double_stack ** nums, char_stack ** signs)
{
    double num1 = double_pop(nums);
    double num2 = double_pop(nums);
    char operation = char_pop(signs);
    if (operation == '+')
        double_push(nums, num1+num2);
    else if (operation == '-')
        double_push(nums, num2-num1);
    else if (operation == '*')
        double_push(nums, num2*num1);
    else if (operation == '/')
        double_push(nums, num2/num1);
}

int main()
{

    FILE * f_in = fopen("input.txt", "r");
    FILE * f_out = fopen("output.txt", "w");

    double_stack * nums = NULL;
    char_stack * signs = NULL;
    char symbol, prev_symbol = '(';
    int read = 1;

    fscanf(f_in, "%c", &symbol);
    for (;symbol!='\0' && symbol!='\n';)
    {
        if (symbol == ' ');
        else if ( (symbol-'0'>=0) && (symbol-'0'<=9) )
        {
            int num = 0;
            int cnt = 0;
            while (((symbol-'0'>=0) && (symbol-'0'<=9)) || (symbol=='.'))
            {
                if (cnt>0)
                    cnt++;
                if (symbol == '.')
                    cnt++;
                num = num*10 + (symbol-'0');
                fscanf(f_in, "%c", &symbol);
            }
            for (int i = 0; i<cnt; i++)
                num/=10;
            double_push(&nums, num);
            read = 0;
            prev_symbol = '0';
        }
        else if (symbol == '+')
        {
            if (is_empty_char(signs))
                char_push(&signs, '+', plus_priority);
            else
            {
                while (is_empty_char(signs) == 0 && plus_priority <= get_priority(signs))
                {
                    make_operation(&nums, &signs);
                }
                char_push(&signs, '+', plus_priority);
            }
            prev_symbol = '+';
        }
        else if (symbol == '-')
        {
            if (prev_symbol == '(')
            {
                char_push(&signs, '-', minus_priority);
                double_push(&nums, 0);
            }
            else
            {
                while (is_empty_char(signs) == 0 && minus_priority <= get_priority(signs))
                {
                    make_operation(&nums, &signs);
                }
                char_push(&signs, '-', minus_priority);
            }
            prev_symbol = '-';
        }
        else if (symbol == '*')
        {
            if (is_empty_char(signs))
                char_push(&signs, '*', mult_priority);
            else
            {
                while (is_empty_char(signs) == 0 && mult_priority <= get_priority(signs))
                {
                    make_operation(&nums, &signs);
                }
                char_push(&signs, '*', mult_priority);
            }
            prev_symbol = '*';
        }
        else if (symbol == '/')
        {
            if (is_empty_char(signs))
                char_push(&signs, '/', div_priority);
            else
            {
                while (is_empty_char(signs) == 0 && div_priority <= get_priority(signs))
                {
                    make_operation(&nums, &signs);
                }
                char_push(&signs, '/', div_priority);
            }
            prev_symbol = '/';
        }
        else if (symbol == '(')
        {
            char_push(&signs, '(', open_bracket_priority);
            prev_symbol = '(';
        }
        else if (symbol == ')')
        {
            while (get_char_elem(signs) != '(')
                make_operation(&nums, &signs);
            char_pop(&signs);
            prev_symbol = ')';
        }

        if (read)
            fscanf(f_in, "%c", &symbol);
        read = 1;
    }

    while (is_empty_char(signs) == 0)
        make_operation(&nums, &signs);

    double ans = double_pop(&nums);
    fprintf(f_out, "%0.20g", ans);

    return 0;
}