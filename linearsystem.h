#ifndef __LINSYS_H__
#define __LINSYS_H__
//error values
#define F_DIVBYZERO -1
#define F_INEXACT -2
#define F_INVALID -4
#define F_OVERFLOW -8
#define F_UNDERFLOW -16
//convergence tests
#define MAXIT 100
#define EPS 1.0e-4

typedef float real_t;

typedef struct {
    int nx, ny;
    real_t hx, hy;
    real_t *A, *b, *y; //Ay = b
} linsys_t;

//TODO: funções (baseadas no .c do dw)
linsys_t* allocLinSys (unsigned int n);
void freeLinSys (linsys_t *ls);
linsys_t *readLinSys(); //?
void printLinSys(linsys_t *ls);
void printArray(real_t *a, unsigned int n);
int gs_5diag(linsys_t *ls);


#endif // __LINSYS_H__
