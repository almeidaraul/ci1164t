#include "getinput.h"

void parse_input (int argc, char **argv, int *nx, int *ny, int *maxit, FILE *output) {
    output = stdout;
    for (int i = 0; i < argc; i++) {
        if (!(strcmp(argv[i], "-i"))) {
            maxit = atoi(argv[i+1]); 
        }
        else if (!(strcmp(argv[i], "-nx"))) {
            nx = atoi(argv[i+1]);
        }
        else if (!(strcmp(argv[i], "-ny"))) {
            ny = atoi(argv[i+1]);
        }
        else if (!(strcmp(argv[i], "-o"))) {
            output = fopen(argv[i+1], "w");
        }
    }
}

void output_dat (FILE *output, linsys_t *ls) {
    real_t xit, yit;
    fprintf(output, "###########\n");
    fprintf(output, "# Tempo Médio GS: %lf\n", ls->avg_time);
    fprintf(output, "###########\n");
    for (int x = 0; x < ls->nx; x++)
        for (int y = 0; y < ls->ny; y++) {
            xit = ls->x0 + ls->hx*x;
            yit = ls->y0 + ls->hy*y;
            fprintf(output, "%rt %rt %rt\n", xit, yit, ls->u[at(x, y)]);
        }
}
