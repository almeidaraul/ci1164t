/*!
 * \file getio.c
 *
 * Funções de entrada e saída para o programa principal
 */
#include "getio.h"

/*!
 * \brief Processa opções dadas na execução do programa (entrada do usuário)
 *
 * Dadas as definições do usuário, oferecidas via linha de comando na execução
 * do programa, esta função atribui os valores adequados às variáveis adequadas.
 *
 * \param argc Número de argumentos na linha de comando (vem de main.c)
 * \param argv Argumentos da linha de comando (vem de main.c)
 * \param nx Número de pontos no eixo das abscissas; influencia a malha da EDP
 * \param ny Número de pontos no eixo das ordenadas; influencia a malha da EDP
 * \param maxit Número máximo de iterações para o método de Gauss-Seidel
 * \param output Arquivo de saída; valor padrão é stdout
 */
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

/*!
 * \brief Salva arquivo .dat com a função computada
 *
 * Gera um arquivo .dat com informações para desenho no gnuplot.
 * Também são incluídos comentários que contemplam o tempo médio para
 * iterações de Gauss-Seidel e valor de resíduo em cada iteração.
 *
 * \param output Arquivo de saída
 * \param ls Ponteiro para a estrutura do sistema linear resolvido
 */
void output_dat (FILE *output, linsys_t *ls) {
	real_t xit, yit;
	fprintf(output, "###########\n");
	fprintf(output, "# Tempo Médio GS: %lf\n", ls->avg_time);
	fprintf(output, "#\n# Norma L2 do Resíduo\n");

	for (int it=0; it < ls->maxit; it++)
		fprintf(output, "# i=%d: %lf\n", it+1, ls->resid[it]);

	fprintf(output, "###########\n");
	for (int x = 0; x < ls->nx; x++)
		for (int y = 0; y < ls->ny; y++) {
			xit = ls->x0 + ls->hx*x;
			yit = ls->y0 + ls->hy*y;
			fprintf(output, "%lf %lf %lf\n", xit, yit, ls->u[AT(x, y)]);
		}
}
