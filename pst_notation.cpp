#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "rpn.h"


void post_notation (int N){
    int max_len = 100;
    int curr_len = 0;
    //char c;

    FILE *fp = fopen("constant_expressions.txt", "r");
    FILE *fw = fopen("postfix_notation.txt", "w");
    char** sp_all = (char**) calloc(N, sizeof(char*));

    assert(sp_all != NULL);
    assert(fp != NULL);



    for (int i = 0; i < N; i++){
        //int j = 0;
        //sp_all[i] = (char*) calloc(max_len, sizeof(char));
        //c = fgetc(fp);

        //while (c != EOF || c != '\n'){
        //    sp_all[i][j] = c;
        //    j++;
        //    c = fgetc(fp);
        //}
        sp_all[i] = (char*) calloc(max_len, sizeof(char));
        fscanf(fp, "%s", sp_all[i]);
        curr_len = (int) strlen(sp_all[i]);
        sp_all[i] = (char*) realloc(sp_all[i], curr_len);



        //c = '\0';
        //sp_all[i][j] = c;
        //sp_all[i] = (char*) realloc(sp_all[i], j + 1);
        sp_all[i] = post_conversion(sp_all[i]);

        fprintf(fw, "%s\0\n", sp_all[i]);
    }

    fclose(fp);
    fclose(fw);
}
