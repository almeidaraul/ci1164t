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

void output_dat (real_t hx, real_t hy, real_t x0, real_t y0, real_t *u, int nx, int ny, FILE *output) {
    real_t xit, yit;
    fprintf(output, "# X Y U\n");
    for (int x = 0; x < nx; x++)
        for (int y = 0; y < ny; y++) {
            xit = x0 + hx*x;
            yit = y0 + hy*y;
            fprintf(output, "%rt %rt %rt\n", xit, yit, u[at(x, y)]);
        }
}
