#include <assert.h>
#include <stdio.h>
#include <stdlib.h>


void post_notation (int N);


void post_notation (int N){
    int max_len = 100;
    char c;

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
        //}

        fscanf(fp, "%s", &sp_all[i]);


        //c = '\0';
        //sp_all[i][j] = c;
        //sp_all[i] = (char*) realloc(sp_all[i], j + 1);
        sp_all[i] = post_conversion(sp_all[i]);

        fprintf(fw, "%s\0\n", sp_all[i]);
    }
    
    fclose(fp);
    fclose(fw);
}
