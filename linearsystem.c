/*!'
 * \file linearsystem.c *
 * Funções que tratam diretamente do sistema linear
 */
#include "linearsystem.h"

/*!
 * \brief Retorna o valor da função f(x, y), apenas para facilitar implementação e leitura
 *
 * \param xi e yi atuais
 */
real_t f(real_t x, real_t y) {
	return (4*_PI*_PI*(sin(2*_PI*x)*sinh(_PI*y) + 
				sin(2*_PI*(_PI-x))*sinh(_PI*(_PI-y))));
}

/*!
 * \brief Inicializa o sistema linear, isto é, atribui a ele os valores corretos para nx, ny, hx, hy, maxit, output e inicializa o vetor solução com o valor de contorno nas bordas e 0 no resto, e o vetor b
 *
 * \param Ponteiro para o sistema linear, número de pontos em x e em y, número de iterações e arquivo de saída
 */
void init_linsys (linsys_t *ls, int num_x, int num_y, int maxit, FILE *out) {
	ls->maxit = maxit;
	ls->nx = num_x;
	ls->ny = num_y;
	ls->hx =((double)(_PI))/((double)(ls->nx-1)); //certo
	ls->hy = ((double)(_PI))/((double)(ls->ny-1)); //certo
	ls->output = out;


	real_t hx, hy;
	hx = ls->hx;
	hy = ls->hy;

	//inicializa matriz B
	for (int i=0; i<ls->nx; i++)
		for (int j=0; j<ls->ny; j++) {
			ls->b[AT(i, j)] = 2*hx*hx*hy*hy*f(x(i), y(j));
//			printf("%lf %lf %d %lf\n", x(i), y(j), AT(i, j), ls->b[AT(i, j)]);			
		}
//	printf("\n");


	//inicializa matriz X
//	printf("sinh(pi²) = %lf\n", sinh(_PI*_PI));
	for (int i=0; i<ls->nx; i++)
		for (int j=0; j<ls->ny; j++) {
			
//			printf("nx = %d, ny = %d\n", i, j);

			if ((i==0) || (i==ls->nx-1)) 
				ls->u[AT(i, j)] = 0;
			else if (j==0)
				ls->u[AT(i, j)] = 
					sin(2*_PI*(_PI-x(i)))*sinh(_PI*_PI);
			else if (j==ls->ny-1)
				ls->u[AT(i, j)] = 
					sin(2*_PI*x(i))*sinh(_PI*_PI);
			else
				ls->u[AT(i, j)] = 0;

//			printf("i = %d, j = %d\n", i, j);
//			printf("%lf %lf %d %lf %lf\n", x(i), y(j), AT(i, j), ls->b[AT(i, j)], ls->u[AT(i, j)]);
		}
//	printf("\n");	
//	for (int i=0; i<ls->nx; i++)
//		for (int j=0; j<ls->ny; j++)
//			printf("%lf %lf %lf\n", x(i), y(j), ls->u[AT(i, j)]);
//	printf("\n");
//	printf("yay\n");


//	printf("yay2\n");
//	printf("f(%lf, %lf) = %lf\n", x(ls->nx-1), y(1), ls->u[AT(ls->nx-1, 1)]);

//	for (int i=0; i<ls->nx; i++)
//		for (int j=0; j<ls->ny; j++) 
//			printf("%lf %lf %lf\n", x(i), y(j), ls->u[AT(i, j)]);
//	printf("\n");
}

/*!
 * \brief Aloca espaço para um sistema linear na memória
 *
 * \return ls Ponteiro para estrutura com espaço alocado
 */
linsys_t *alloc_linsys (int nx, int ny, int maxit) {
	linsys_t *ls = (linsys_t *) malloc(sizeof(linsys_t));
//	printf("size = %d\n", nx*ny);
	ls->u = (real_t *) malloc((nx)*(ny)*sizeof(real_t));
	ls->b = (real_t *) malloc((nx)*(ny)*sizeof(real_t));
	ls->resid = (real_t *) malloc(maxit*sizeof(real_t));
	return ls;
}

/*!
 * \brief Libera o espaço de um sistema linear na memória
 *
 * \param ls Ponteiro para o sistema a ser limpo
 */
void free_linsys (linsys_t *ls) {
	free(ls->u);
	free(ls->b);
	free(ls->resid);
	free(ls);
}


/*!
 * \brief Calcula o resíduo do sistema linear
 *
 * \param Ponteiro para o sistem linear
 * \return Residuo para a iteração atual
 */
real_t residuo (linsys_t *ls) {

	real_t r = 0, aux, hx, hy;
	hx = ls->hx;
	hy = ls->hy;

	for(int i = 1; i < ls->nx-1; i++)				//talvez nx-1? (borda direita)
		for(int j = 1; j < ls->ny-1; j++) {			//idem
			aux = ls->b[AT(i, j)] 
					+ ls->u[AT(i+1, j)]*(2*hy*hy-hx*hy*hy)
					+ ls->u[AT(i-1, j)]*(2*hy*hy+hx*hy*hy)
					+ ls->u[AT(i, j+1)]*(2*hx*hx-hx*hx*hy)
					+ ls->u[AT(i, j-1)]*(2*hx*hx+hx*hx*hy)
					- ls->u[AT(i, j)]*(4*hy*hy + 4*hx*hx + 8*PI_SQUARED*hx*hx*hy*hy);
			r += aux*aux;
		}
	return sqrt(r);
}

/*!
 * \brief Aplica o método de Gauss-Seidel para resolução de um dado sistema
 *
 * Aplica o Gauss-Seidel pentadiagonal em uma estrutura de sistema linear dada
 *
 * \param ls Ponteiro para o sistema linear a ser resolvido
 * \return estado 0 ou código de erro
 */
int gs_5diag(linsys_t *ls) {

//	printf("entrando no gauss seidel\n");


	real_t xi, yi, hy, hx; 
	hy = ls->hy;
	hx = ls->hx;
	unsigned int i, j, it;
	double start_time, time_sum = 0.0;

//	for (int i=0; i<ls->nx; i++)
//		for (int j=0; j<ls->ny; j++) 
//			printf("%lf %lf %lf\n", x(i), y(j), ls->u[AT(i, j)]);

//	printf("f(%lf, %lf) = %lf\n", x(ls->nx-1), y(1), ls->u[AT(ls->nx-1, 1)]);
//	printf("prestes a entrar no loop\n");
	for (it = 0; it < ls->maxit; it++) {
		start_time = timestamp();
		for(i = 1; i < ((ls->nx)-1); i++)				//talvez nx-1? (borda direita)
			for(j = 1; j < ((ls->ny)-1); j++) {			//idem

//				printf("it = %d, nx = %d, ny = %d\n", it, i, j);
//				double a1, a2, a3, a4, a5;

//					printf("%d*%d+%d = AT[a1] = %d\n", i, ls->nx, j, AT(i, j));
//					a1 = ls->b[AT(i, j)]; 
//					printf("a1 = %lf\n", a1);
//
//					printf("%d*%d+%d = AT[a2] = %d\n", i+1, ls->nx, j, AT(i+1, j));
//					a2 = ls->u[AT(i+1, j)]*(2*hy*hy-hx*hy*hy);
//					printf("a2 = %lf\n", a2);
//
//					printf("%d*%d+%d = AT[a3] = %d\n", i-1, ls->nx, j, AT(i-1, j));
//					a3 = ls->u[AT(i-1, j)]*(2*hy*hy+hx*hy*hy);
//					printf("a3 = %lf\n", a3);
//
//					a4 = ls->u[AT(i, j+1)]*(2*hx*hx-hx*hx*hy);
//					printf("a4 = %lf\n", a4);
//
//					a5 = ls->u[AT(i, j-1)]*(2*hx*hx+hx*hx*hy);
//					printf("a5 = %lf\n\n", a5);


				xi = ls->x0 + i*ls->hx;
				yi = ls->y0 + j*ls->hy;
				ls->u[AT(i, j)] = //the N word
					(ls->b[AT(i, j)] 
					 + ls->u[AT(i+1, j)]*(2*hy*hy-hx*hy*hy)
					 + ls->u[AT(i-1, j)]*(2*hy*hy+hx*hy*hy)
					 + ls->u[AT(i, j+1)]*(2*hx*hx-hx*hx*hy)
					 + ls->u[AT(i, j-1)]*(2*hx*hx+hx*hx*hy))
					 /(4*hy*hy
							 +4*hx*hx
							 +8*PI_SQUARED*hx*hx*hy*hy
					  );
			}
		time_sum += timestamp() - start_time;
		ls->resid[it] = residuo(ls);
	}
	ls->avg_time = time_sum/ls->maxit;
//	printf("yaay3\n");
	return 0;
}



