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
//likwid
#ifdef LIKWID_PERFMON
#include <likwid.h>
#else
#define LIKWID_MARKER_INIT
#define LIKWID_MARKER_THREADINIT
#define LIKWID_MARKER_SWITCH
#define LIKWID_MARKER_REGISTER(regionTag)
#define LIKWID_MARKER_START(regionTag)
#define LIKWID_MARKER_STOP(regionTag)
#define LIKWID_MARKER_CLOSE
#define LIKWID_MARKER_GET(regionTag, nevents, events, time, count)
#endif
//convergence tests
#define EPS 1.0e-4
//indexing
#define AT(row, col) (row)*ls->ny + (col)
#define l (_PI-0)
#define x(i) (0+(i)*hx)
#define y(j) (0+(j)*hy)

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
linsys_t* alloc_linsys (int nx, int ny, int maxit);
void free_linsys (linsys_t *ls);
int gs_5diag(linsys_t *ls);

#endif // __LINSYS_H__
