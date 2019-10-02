/*!
 * \file getio.h
 *
 * Utilidades de entrada e saída
 */
#include <string.h>
#include "linearsystem.h"

void parse_input (int argc, char **argv, int *nx, int *ny, int *maxit, FILE *output);
void output_dat (FILE *output, linsys_t *ls);

void cmd_itp (int argc, char *argv[], int *nx, int *ny, int *maxit, char *output_name);
