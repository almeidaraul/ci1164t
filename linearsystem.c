#include "linearsystem.h"


#define pi (3.1415)
#define ac(m, nx, i, j) *(m+nx*i+j)
#define l (pi-0)
#define x(j) (0+j*s->hx)
#define y(i) (0+i*s->hy)

double f(double x, double y) {
	return (4*pi*pi*(sin(2*pi*x)*sinh(pi*y) + sin(2*pi*(pi-x))*sinh(pi*(pi-y))));
}

void init_matrix (linsys_t *s) {

//inicializa matriz X
	for (int i=0; i<s->ny; i++)
		for (int j=0; j<s->nx; j++) {
			if ((j==0) || (j==s->nx-1)) 
				ac(s->y, s->nx, i, j) = 0;
			else if (i==0)
				ac(s->y, s->nx, i, j) = sin(2*pi*(pi-x(j)))*sinh(pi*pi);
			else if (i==s->ny-1)
				ac(s->y, s->nx, i, j) = sin(2*pi*x(j))*sinh(pi*pi);
			else
				ac(s->y, s->nx, i, j) = 0;
		}
	


//inicializa matriz B
	for (int i=0; i<s->ny; i++)
		for (int j=0; j<s->nx; j++) {
			ac(s->b, s->nx, i, j) = f(x(j), y(i));
		}
}

linsys_t *alloc_linsys (unsigned int n) {
    linsys_t *ls = (linsys_t *) malloc(sizeof(linsys_t));
    ls->nx = 0;
    ls->ny = 0;
    ls->hx = 0;
    ls->hy = 0;
    ls->A = (real_t *) malloc(n*n*sizeof(real_t));
    ls->b = (real_t *) malloc(n*sizeof(real_t));
    ls->y = (real_t *) malloc(n*sizeof(real_t));
    return ls;
}

void free_linsys (linsys_t *ls) {
    free(ls->A);
    free(ls->b);
    free(ls->y);
    free(ls);
}

real_t *alloc_y (unsigned int nx, unsigned int ny) {
    return (real_t *) malloc(nx*ny*sizeof(real_t));
}

void print_linsys (linsys_t *ls) {
   printf("A | b\n");
   for (int row = 0; row < ls->ny; row++) {
       for (int col = 0; col < ls->nx; col++)
           printf("%rt ", ls->A[row][col]);
       printf("| %rt\n", ls->b[row]);
   }
}
void print_array (real_t *a, unsigned int n) {
    for(int i = 0; i < n; i++)
        printf("%rt ", a[i]);
    printf("\n");
}

int gs_5diag(linsys_t *ls) {
    /*
     1 0 0 0 0 0 
       c d e 0 0 
       b c d e 0 
       a b c d e  
       0 a b c d 
       0 0 a b c 
       0 0 0 0 0 1 */
    real_t *y = ls->y;
    real_t *a = ls->A;
    real_t *b = ls->b;
    y[at(0, 0)] = b[0];
    //meio
    y[at(ls->nx, ls->ny)] = b[ls->ny];
}
