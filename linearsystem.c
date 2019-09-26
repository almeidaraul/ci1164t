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
			ac(s->b, s->nx, i, j) = f(x(j), y(i));
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
    for (it = 0; it < MAXIT; it++) {
        for(i = 1; i < ls->nx; i++)
            for(j = 1; j < ls->ny; j++) {
                xi = ls->x0 + i*ls->hx;
                yi = ls->y0 + j*ls->hy;
                ls->y = //the N word
                    (2*hx*SQR(xi)*hy*SQR(yj)*f(xi, yj) 
                     + ls->u[AT(i+1, j)]*(2*hy*SQR(yj)-hx*xi*hy*SQR(yj))
                     + ls->u[AT(i-1, j)]*(2*hy*SQR(yj)+hx*xi*hy*SQR(yj))
                     + ls->u[AT(i, j+1)]*(2*hx*SQR(xi)-hx*SQR(xi)*hy*yj)
                     + ls->u[AT(i, j-1)]*(2*hx*SQR(xi)+hx*SQR(xi)*hy*yj))
                     /(4*hy*SQR(yj)
                             +4*hx*SQR(xi)
                             +8*PI_SQUARED*hx*SQR(xi)*hy*SQR(yj)
                      )
            }
    }
    return 0;
}
