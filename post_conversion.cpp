#include "rpn.h"
#include "stackT.h"

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <ctype.h>

const int DEFAULT_STR_LEN = 100;
const int DEFAULT_STACK_CAP = 10;
const int STR_LEN_MULTIPLIER = 2;

const int PRIO_MAX = 100;
const int PRIO_HIGH = 50;
const int PRIO_MED = 25;
const int PRIO_LOW = 10;
const int PRIO_MIN = 0;

char* post_conversion(char *str)
{
    assert(str);

    char *res = (char*)calloc(DEFAULT_STR_LEN, sizeof(char));
    assert(res);

    int current_res_len = DEFAULT_STR_LEN;

    SStack<char> stack;
    stack_constructor(&stack, DEFAULT_STACK_CAP);

    int chars_processed = 0;

    while(*str)
    {
        if(chars_processed >= current_res_len)
        {
            current_res_len *= STR_LEN_MULTIPLIER;
            res = (char*)realloc(res, current_res_len);
        }

        if(isdigit(*str))
        {
            res[chars_processed] = *str;
            chars_processed++;
            str++;
        }
        else if(*str == '(')
        {
            push_in_stack(&stack, '(');
            str++;
        }
        else if(*str == ')')
        {
            char stack_char = 0;
            pop_from_stack(&stack, &stack_char);

            while(stack_char != '(')
            {
                res[chars_processed] = stack_char;
                chars_processed++;

                pop_from_stack(&stack, &stack_char);
            }

            str++;
        }
        else if(is_op(*str))
        {
            if(stack_is_empty(&stack))
            {
                push_in_stack(&stack, *str);
                str++;
            }
            else
            {
                char stack_char = 0;
                peek_from_stack(&stack, &stack_char);

                switch(*str)
                {
                    case '^':
                        if(stack_char == '^')
                        {
                            res[chars_processed++] = stack_char;
                            pop_from_stack(&stack, &stack_char);
                        }
                        else
                        {
                            push_in_stack(&stack, '^');
                            str++;
                        }
                        break;
                    case '*':
                        if(stack_char == '^')
                        {
                            res[chars_processed++] = stack_char;
                            pop_from_stack(&stack, &stack_char);
                        }
                        else
                        {
                            push_in_stack(&stack, '*');
                            str++;
                        }
                        break;
                    case '/':
                        if(stack_char == '^')
                        {
                            res[chars_processed++] = stack_char;
                            pop_from_stack(&stack, &stack_char);
                        }
                        else
                        {
                            push_in_stack(&stack, '/');
                            str++;
                        }
                        break;
                    case '+':
                        if(stack_char == '^' || stack_char == '*' || stack_char == '/')
                        {
                            res[chars_processed++] = stack_char;
                            pop_from_stack(&stack, &stack_char);
                        }
                        else
                        {
                            push_in_stack(&stack, '+');
                            str++;
                        }
                        break;
                    case '-':
                        if(stack_char == '^' || stack_char == '*' || stack_char == '/')
                        {
                            res[chars_processed++] = stack_char;
                            pop_from_stack(&stack, &stack_char);
                        }
                        else
                        {
                            push_in_stack(&stack, '-');
                            str++;
                        }
                        break;
                    default:
                        printf("Vse pogano\n");
                }
            }
        }
    }

    while(!stack_is_empty(&stack))
    {
        char stack_char = 0;
        pop_from_stack(&stack, &stack_char);

        res[chars_processed++] = stack_char;
    }

    //printf("%s\n", res);

    return res;
}

int is_op(char chr)
{
    if(chr == '+' || chr == '-' || chr == '*' || chr == '/' || chr == '^') return 1;

    return 0;
}
