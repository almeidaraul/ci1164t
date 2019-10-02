/*!
 * \file main.c
 *
 * Programa principal; interface entre as funções
 */
#include "linearsystem.h"
#include "getio.h"
#include "errors.h"

int main(int argc, char **argv) {
	int nx, ny, maxit;
	FILE *output;
	parse_input (argc, argv, &nx, &ny, &maxit, output);
	linsys_t *ls = alloc_linsys();
	init_linsys(ls, nx, ny, maxit, output);
	print_error(gs_5diag(ls));
	return 0;
}
