#include <stdio.h>
#include <stdlib.h>
#include "constExprExtracter.hpp"

static const char *inFileName = "program.txt";

static const char *outFileName = "constant_expressions.txt";

static int extractConsts(FILE *in, FILE *out)
{

    int constExprCount = 0;

    while (!feof(in))
    {
        fscanf(in, "%*[^=]");
        fscanf(in, "%*[=]");

        long currOffset = ftell(in);

        unsigned constExprLen = 0;
        fscanf(in, "%*[()0-9+*/^-]%n", &constExprLen);
        if (constExprLen == 0)
            return constExprCount;

        fseek(in, currOffset, SEEK_SET);

        char *constExpr = (char *)calloc(constExprLen + 1, sizeof(char));

        fscanf(in, "%[()0-9+*/^-]", constExpr);

        constExpr[constExprLen] = '\n';

        fwrite(constExpr, sizeof(char), constExprLen + 1, out);

        constExprCount++;

        free(constExpr);
    }

    return constExprCount;
}

int clipping_expressions()
{
    FILE *in = fopen(inFileName, "r");
    if (in == NULL)
    {
        perror(inFileName);
        return -1;
    }
    FILE *out = fopen(outFileName, "w");
    if (out == NULL)
    {
        perror(outFileName);
        return -1;
    }

    int res = extractConsts(in, out);
    fclose(in);
    fclose(out);
    return res;
}
