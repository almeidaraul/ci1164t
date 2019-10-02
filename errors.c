/*!
 * \file errors.c
 * 
 * Utilidades para interpretação e informação (ao usuário) de erros no sistema
 */
#include "errors.h"

/*!
 * \brief Imprime um dado erro em stderr (e seu significado)
 *
 * \param errnum Código do erro recebido
 */
void print_error (int errnum) {
	fprintf(stderr, "Execution found error ");
	switch (errnum) {
		case (F_DIVBYZERO):
			fprintf(stderr, "F_DIVBYZERO\n  Float division by zero\n");
			break;
		case (F_INEXACT):
			fprintf(stderr, "F_INEXACT\n  Float inexact value\n");
			break;
		case (F_INVALID):
			fprintf(stderr, "F_INVALID\n  Float invalid value\n");
			break;
		case (F_OVERFLOW):
			fprintf(stderr, "F_OVERFLOW\n  Float overflow\n");
			break;
		case (F_UNDERFLOW):
			fprintf(stderr, "F_UNDERFLOW\n	Float underflow\n");
			break;
	}
}
