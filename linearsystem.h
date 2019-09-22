#ifndef __LINSYS_H__
#define __LINSYS_H__
#include <math.h>
//error values
#define F_DIVBYZERO -1
#define F_INEXACT -2
#define F_INVALID -4
#define F_OVERFLOW -8
#define F_UNDERFLOW -16
//convergence tests
#define MAXIT 100
#define EPS 1.0e-4
//indexing
#define at(row, col) row*ls->nx + col

typedef double real_t;
//for printing real_t
#define %rt %lf

typedef struct {
    int nx, ny;
    real_t hx, hy, x0, y0, xn, yn;
    real_t *A, *b, *y; //Ay = b
} linsys_t;

//TODO: funções (baseadas no .c do dw)
linsys_t* alloc_linsys (unsigned int n);
void free_linsys (linsys_t *ls);
real_t *alloc_y (unsigned int nx, unsigned int ny);
linsys_t *read_linsys(); //?
void print_linsys(linsys_t *ls);
void print_array(real_t *a, unsigned int n);
int gs_5diag(linsys_t *ls);


#endif // __LINSYS_H__
