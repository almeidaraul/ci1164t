#include "linearsystem.h"

linsys_t *alloc_linsys (unsigned int n) {
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

void free_linsys (linsys_t *ls) {
    free(ls->A);
    free(ls->b);
    free(ls->y);
    free(ls);
}

real_t *alloc_y (unsigned int nx, unsigned int ny) {
    return (real_t *) malloc(nx*ny*sizeof(real_t));
}

void print_linsys (linsys_t *ls) {
   printf("A | b\n");
   for (int row = 0; row < ls->ny; row++) {
       for (int col = 0; col < ls->nx; col++)
           printf("%rt ", ls->A[row][col]);
       printf("| %rt\n", ls->b[row]);
   }
}
void print_array (real_t *a, unsigned int n) {
    for(int i = 0; i < n; i++)
        printf("%rt ", a[i]);
    printf("\n");
}

int gs_5diag(linsys_t *ls) {
}
