#include "linearsystem.h"

#define ac(m, nx, i, j) *(m+nx*i+j)
#define l (_PI-0)
#define x(j) (0+j*s->hx)
#define y(i) (0+i*s->hy)

real_t f(real_t x, real_t y) {
	return (4*_PI*_PI*(sin(2*_PI*x)*sinh(_PI*y) + 
                sin(2*_PI*(_PI-x))*sinh(_PI*(_PI-y))));
}

void init_linsys (linsys_t *s) {
    //inicializa matriz X
	for (int i=0; i<s->ny; i++)
		for (int j=0; j<s->nx; j++) {
			if ((j==0) || (j==s->nx-1)) 
				ac(s->y, s->nx, i, j) = 0;
			else if (i==0)
				ac(s->y, s->nx, i, j) = 
                    sin(2*_PI*(_PI-x(j)))*sinh(_PI*_PI);
			else if (i==s->ny-1)
				ac(s->y, s->nx, i, j) = 
                    sin(2*_PI*x(j))*sinh(_PI*_PI);
			else
				ac(s->y, s->nx, i, j) = 0;
		}
    //inicializa matriz B
	for (int i=0; i<s->ny; i++)
		for (int j=0; j<s->nx; j++) 
			ac(s->b, s->nx, i, j) = 2*hx*hx*hy*hy*f(x(j), y(i));
}

linsys_t *alloc_linsys (int num_x, int num_y) {
    linsys_t *ls = (linsys_t *) malloc(sizeof(linsys_t));
    ls->nx = num_x;
    ls->ny = num_y;
    ls->hx = l/(ls->nx-1);
    ls->hy = l/(ls->ny-1);
    ls->y = (real_t *) malloc(num_x*num_y*sizeof(real_t));
    return ls;
}

void free_linsys (linsys_t *ls) {
    free(ls->u);
    free(ls);
}

void print_array (real_t *a, unsigned int n) {
    for(int i = 0; i < n; i++)
        printf("%rt ", a[i]);
    printf("\n");
}

int gs_5diag(linsys_t *ls) {
    real_t xi, yj, hy = ls->hy, hx = ls->hx;
    unsigned int i, j, it;
    double start_time, time_sum = 0.0;
    for (it = 0; it < MAXIT; it++) {
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
    }
    ls->avg_time = time_sum/MAXIT;
    return 0;
}


double residuo (linsys_t *ls) {

	double r = 0, aux;

	for(i = 1; i < ls->nx-1; i++)				//talvez nx-1? (borda direita)
		for(j = 1; j < ls->ny-1; j++) {			//idem
			aux = ls->b[AT(i, j)] 
                    + ls->u[AT(i+1, j)]*(2*hy*hy-hx*hy*hy)
                    + ls->u[AT(i-1, j)]*(2*hy*hy+hx*hy*hy)
                    + ls->u[AT(i, j+1)]*(2*hx*hx-hx*hx*hy)
                    + ls->u[AT(i, j-1)]*(2*hx*hx+hx*hx*hy)
					- ls->u[AT(i, j)]*(4*hy*hy + 4*hx*hx + 8*PI_SQUARED*hx*hx*hy*hy;
			r += aux*aux;
		}
	return sqrt(r);
}
