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
