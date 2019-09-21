#include "linearsystem.h"

linsys_t *allocLinSys (unsigned int n) {
    linsys_t *ls = (linsys_t *) malloc(sizeof(linsys_t));
    ls->nx = 0;
    ls->ny = 0;
    ls->hx = 0;
    ls->hy = 0;
    ls->A = (real_t *) malloc(n*n*sizeof(real_t));
    ls->b = (real_t *) malloc(n*sizeof(real_t));
    ls->y = (real_t *) malloc(n*sizeof(real_t));
    return ls;
}

void freeLinSys (linsys_t *ls) {
    free(ls->A);
    free(ls->b);
    free(ls->y);
    free(ls);
}

int gs_5diag(linsys_t *ls) {
}
