#ifndef __LINSYS_H__
#define __LINSYS_H__
//constants
#define _PI 3.14159265358979323846
#define PI_SQUARED 9.869604401089358
#define SINH_PS 9666.84451132098 //sinh(PI_SQUARED)
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
    real_t hx, hy, x0, y0, xN, yN;
    real_t *u; 
} linsys_t;

real_t f(real_t x, real_t y);
void init_linsys(linsys_t *s);
linsys_t* alloc_linsys (unsigned int n);
void free_linsys (linsys_t *ls);
void print_array(real_t *a, unsigned int n);
int gs_5diag(linsys_t *ls);


#endif // __LINSYS_H__
