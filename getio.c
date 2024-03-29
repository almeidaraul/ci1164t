/*!
 * \file getio.c
 *
 * Funções de entrada e saída para o programa principal
 */
#include "getio.h"

/*!
 * \brief Lê entrada e faz as atribuições adequadas
 *
 * Lê, da linha de comando, o número de pontos em X, o número de pontos em Y,
 * o número máximo de iterações e o arquivo de saída (se não houver, atribui
 * a saída padrão)
 *
 * \param argc Número de argumentos na entrada
 * \param argv Argumentos na linha de comando
 * \param nx Número de pontos em X
 * \param ny Número de pontos em Y
 * \param maxit Número máximo de iterações do método de Gauss-Seidel
 * \param output Arquivo onde deve ser escrita a saída
 */
void parse_input (int argc, char **argv, int *nx, int *ny, int *maxit, FILE **output) {
	*output = stdout;

	for (int i = 0; i < argc; i++) {
		if (!(strcmp(argv[i], "-i"))) {
			*maxit = atoi(argv[i+1]); 
		}
		else if (!(strcmp(argv[i], "-nx"))) {
			*nx = atoi(argv[i+1])+2;
		}
		else if (!(strcmp(argv[i], "-ny"))) {
			*ny = atoi(argv[i+1])+2;
		}
		else if (!(strcmp(argv[i], "-o"))) {
			*output = fopen(argv[i+1], "w");
		}
	}
	

}

/*!
 * \brief Escreve arquivo "plotável" da função computada
 *
 * Escreve, num arquivo .dat de nome especificado pelo usuário (ou stdout),
 * comentários informando sobre a execução do algoritmo (tempo médio de uma
 * iteração de Gauss-Seidel, resíduo por iteração) e os próprios pontos a
 * serem desenhados pelo gnuplot
 *
 * \param ls Estrutura do sistema linear
 */
void output_dat (linsys_t *ls) {


	real_t xit, yit;

	fprintf(ls->output, "###########\n");
	fprintf(ls->output, "# Tempo Médio GS: %lf\n", ls->avg_time);
	fprintf(ls->output, "#\n# Norma L2 do Resíduo\n");

	for (int it=1; it <= ls->maxit; it++)
		fprintf(ls->output, "# i=%d: %lf\n", it, ls->resid[it]);

	fprintf(ls->output, "###########\n");
	for (int x = 0; x < ls->nx; x++)
		for (int y = 0; y < ls->ny; y++) {
			xit = ls->x0 + ls->hx*x;
			yit = ls->y0 + ls->hy*y;
			fprintf(ls->output, "%lf %lf %lf\n", xit, yit, ls->u[AT(x, y)]);
		}
}

/*!
 * \brief Escreve um vetor na saída padrão. Usado em testes
 *
 * \param a Vetor
 * \param n Tamanho do vetor
 */
void print_array (real_t *a, unsigned int n) {
	for(int i = 0; i < n; i++)
		printf("%lf ", a[i]);
	printf("\n");
}
