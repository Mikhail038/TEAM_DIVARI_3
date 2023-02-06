#include "rpn.h"

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>
#include <sys/stat.h>
#include <sys/mman.h>

struct file_t {
        FILE *stream;
        struct stat stats {};
};

static void
get_file(const char *filename, file_t *file, const char *mode)
{
        assert (filename);
        assert(file);

        if ((file->stream = fopen(filename, mode)) == nullptr) {
                return;
        }

        if (stat(filename, &file->stats) != 0) {
                return;
        }
}

static void
read_file(char **buffer, file_t *file)
{
        assert(file);

        *buffer = (char *) mmap(NULL, (size_t) file->stats.st_size, PROT_READ,
                               MAP_PRIVATE, fileno(file->stream), 0);

        if (*buffer == MAP_FAILED) {
                return;
        }
}

void calculating_value()
{
        // Create stack.
        SStack<int> stk {};
        stack_constructor(&stk, 300);

        // Read input file.
        file_t input {};
        get_file("postfix_notation.txt", &input, "r");
        char *buffer = nullptr;
        read_file(&buffer, &input);

        // Create output file.
        file_t output {};
        get_file("rez.dat", &output, "w");

        // Count number of lines.
        int lines = 0;
        for (int i = 0; i < input.stats.st_size; i++) {
                int ch = buffer[i];
                if(ch == '\n')
                {
                    lines++;
                }
        }
        // Allocate memory for output data.
        int *rez = (int *) calloc(lines, sizeof(int));

        int count = 0;
        for (int i = 0; i < input.stats.st_size; i++) {
                // Check if EOL, end calculation if yes.
                if (buffer[i] == '\n') {
                        int num = 0;
                        pop_from_stack(&stk, &num);
                        rez[count++] = num;
                }

                if(isdigit(*buffer)) {
                        int num = buffer[i] - 48;
                        // Push num.
                } else {
                        int num1 = 0;
                        int num2 = 0;
                        pop_from_stack(&stk, &num1);
                        pop_from_stack(&stk, &num2);

                        switch (buffer[i]) {
                                case '+':
                                        push_in_stack(&stk, num1 + num2);
                                        break;
                                case '-':
                                        push_in_stack(&stk, num2 - num1);
                                        break;
                                case '/':
                                        push_in_stack(&stk, num2 / num1);
                                        break;
                                case '*':
                                        push_in_stack(&stk, num1 * num2);
                                        break;
                                default:
                                        fprintf(stderr, "Encountered '%c'\n", buffer[i]);
                                        assert(0 && "Invalid symbol.\n");
                                        break;
                        }
                }
        }


        // Write output to file.
        for (int i = 0; i < input.stats.st_size; i++)
        {
                fprintf(output.stream, "%d\n", rez[i]);
        }
}
