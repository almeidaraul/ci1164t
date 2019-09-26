#include "errors.h"

void print_error (int errnum, char *func_name, char *line) {
    //TODO: especificar em qual função aconteceu o erro
    fprintf(stderr, "ERROR IN FUNCTION %s, LINE '%s':\n", func_name, line);
    switch (errnum) {
        case (F_DIVBYZERO):
            fprintf(stderr, "F_DIVBYZERO\n");
            break;
        case (F_INEXACT):
            fprintf(stderr, "F_INEXACT\n");
            break;
        case (F_INVALID):
            fprintf(stderr, "F_INVALID\n");
            break;
        case (F_OVERFLOW):
            fprintf(stderr, "F_OVERFLOW\n");
            break;
        case (F_UNDERFLOW):
            fprintf(stderr, "F_UNDERFLOW\n");
            break;
    }
}
