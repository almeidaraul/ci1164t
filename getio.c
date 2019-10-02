/*!
 * \file getio.c
 *
 * Funções de entrada e saída para o programa principal
 */
#include "getio.h"

void parse_input (int argc, char **argv, int *nx, int *ny, int *maxit, FILE *output) {
	output = stdout;
	for (int i = 0; i < argc; i++) {
		if (!(strcmp(argv[i], "-i"))) {
			*maxit = atoi(argv[i+1]); 
		}
		else if (!(strcmp(argv[i], "-nx"))) {
			*nx = atoi(argv[i+1]);
		}
		else if (!(strcmp(argv[i], "-ny"))) {
			*ny = atoi(argv[i+1]);
		}
		else if (!(strcmp(argv[i], "-o"))) {
			output = fopen(argv[i+1], "w");
		}
	}
}

void output_dat (linsys_t *ls) {
	real_t xit, yit;
	fprintf(ls->output, "###########\n");
	fprintf(ls->output, "# Tempo Médio GS: %lf\n", ls->avg_time);
	fprintf(ls->output, "#\n# Norma L2 do Resíduo\n");

	for (int it=0; it < ls->maxit; it++)
		fprintf(ls->output, "# i=%d: %lf\n", it+1, ls->resid[it]);

	fprintf(ls->output, "###########\n");
	for (int x = 0; x < ls->nx; x++)
		for (int y = 0; y < ls->ny; y++) {
			xit = ls->x0 + ls->hx*x;
			yit = ls->y0 + ls->hy*y;
			fprintf(ls->output, "%lf %lf %lf\n", xit, yit, ls->u[AT(x, y)]);
		}
}

void print_array (real_t *a, unsigned int n) {
	for(int i = 0; i < n; i++)
		printf("%lf ", a[i]);
	printf("\n");
}
