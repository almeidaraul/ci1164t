/*!
 * \file linearsystem.h
 *
 * Definições para linearsystem.c
 */
#ifndef __LINSYS_H__
#define __LINSYS_H__
#include <stdlib.h>
#include <stdio.h>
#include "utils.h"
//constants
#define _PI 3.14159265358979323846
#define PI_SQUARED 9.869604401089358
#define SINH_PS 9666.84451132098 //sinh(PI_SQUARED)
//convergence tests
#define EPS 1.0e-4
//indexing
#define AT(row, col) (row)*ls->nx + (col)
#define l (_PI-0)
#define x(j) (0+(j)*hx)
#define y(i) (0+(i)*hy)

typedef double real_t;

typedef struct {
	int nx, ny, maxit;
	real_t hx, hy, x0, y0, xN, yN;
	real_t *u, *b, *resid; 
	double avg_time;
	FILE *output;
} linsys_t;

real_t f(real_t x, real_t y);
void init_linsys(linsys_t *ls, int num_x, int num_y, int maxit, FILE *out);
linsys_t* alloc_linsys ();
void free_linsys (linsys_t *ls);
int gs_5diag(linsys_t *ls);

#endif // __LINSYS_H__
