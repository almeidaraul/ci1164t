/*!
 * \file getio.h
 *
 * Utilidades de entrada e saída
 */
#include <string.h>
#include "linearsystem.h"
//for printing real_t
#define rt %lf

void parse_input (int argc, char **argv, int *nx, int *ny, int *maxit, FILE *output);
void output_dat (linsys_t *ls);
void print_array(real_t *a, unsigned int n);
