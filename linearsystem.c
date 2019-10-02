/*!
 * \file linearsystem.c
 *
 * Funções que tratam diretamente do sistema linear
 */
#include "linearsystem.h"

//#define ac(m, nx, i, j) *(m+nx*i+j)
#define l (_PI-0)
#define x(j) (0+j*hx)
#define y(i) (0+i*hy)

real_t f(real_t x, real_t y) {
	return (4*_PI*_PI*(sin(2*_PI*x)*sinh(_PI*y) + 
				sin(2*_PI*(_PI-x))*sinh(_PI*(_PI-y))));
}

void init_linsys (linsys_t *ls) {
	real_t hx, hy;
	hx = ls->hx;
	hy = ls->hy;
	//inicializa matriz X
	for (int i=0; i<ls->ny; i++)
		for (int j=0; j<ls->nx; j++) {
			if ((j==0) || (j==ls->nx-1)) 
				ls->u[AT(i, j)] = 0;
			else if (i==0)
				ls->u[AT(i, j)] = 
					sin(2*_PI*(_PI-x(j)))*sinh(_PI*_PI);
			else if (i==ls->ny-1)
				ls->u[AT(i, j)] = 
					sin(2*_PI*x(j))*sinh(_PI*_PI);
			else
				ls->u[AT(i, j)] = 0;
		}
	//inicializa matriz B
	for (int i=0; i<ls->ny; i++)
		for (int j=0; j<ls->nx; j++) 
			ls->b[AT(i, j)] = 2*hx*hx*hy*hy*f(x(j), y(i));
}

/*!
 * \brief Aloca espaço para um sistema linear na memória
 *
 * Aloca espaço para a estrutura do sistema linear e para estruturas internas
 * registradas por ponteiros
 *
 * \param num_x Número de pontos nas abscissas
 * \param num_y Númro de pontos nas ordenadas
 * \return Ponteiro para o sistema linear alocado
 */
linsys_t *alloc_linsys (int num_x, int num_y, int maxit) {
	linsys_t *ls = (linsys_t *) malloc(sizeof(linsys_t));
	ls->maxit = maxit;
	ls->nx = num_x;
	ls->ny = num_y;
	ls->hx = l/(ls->nx-1);
	ls->hy = l/(ls->ny-1);
	ls->u = (real_t *) malloc(num_x*num_y*sizeof(real_t));
	ls->b = (real_t *) malloc(num_x*num_y*sizeof(real_t));
	ls->resid = (real_t *) malloc(ls->maxit*sizeof(real_t));
	return ls;
}

void free_linsys (linsys_t *ls) {
	free(ls->u);
	free(ls->b);
	free(ls->resid);
	free(ls);
}

void print_array (real_t *a, unsigned int n) {
	for(int i = 0; i < n; i++)
		printf("%lf ", a[i]);
	printf("\n");
}

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

int gs_5diag(linsys_t *ls) {
	real_t xi, yi, hy, hx; 
	hy = ls->hy;
	hx = ls->hx;
	unsigned int i, j, it;
	double start_time, time_sum = 0.0;
	for (it = 0; it < ls->maxit; it++) {
		start_time = timestamp();
		for(i = 1; i < ls->nx-1; i++)				//talvez nx-1? (borda direita)
			for(j = 1; j < ls->ny-1; j++) {			//idem
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
	return 0;
}



