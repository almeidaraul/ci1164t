/*!
 * \file errors.c
 * 
 * Utilidades para interpretação e informação (ao usuário) de erros no sistema
 */
#include "errors.h"

/*!
 * \brief Imprime em stderr informações sobre erros encontrados na execução
 *
 * Dado um erro e seu contexto (nome de função e linha de código), a função
 * repassa ao usuário - através do canal stderr - o significado do número do
 * erro e seu contexto.
 *
 * \param errnum código de erro recebido
 * \param func_name string que dá nome à função onde ocorreu o erro
 * \param line string com texto da linha onde provavelmente ocorreu o erro
 */
void print_error (int errnum, char *func_name, char *line) {
	fprintf(stderr, "ERROR IN FUNCTION %s, LINE '%s':\n", func_name, line);
	switch (errnum) {
		case (F_DIVBYZERO):
			fprintf(stderr, "F_DIVBYZERO\n");
			break;
		case (F_INEXACT):
			fprintf(stderr, "F_INEXACT\n");
			break;
		case (F_INVALID):
			fprintf(stderr, "F_INVALID\n");
			break;
		case (F_OVERFLOW):
			fprintf(stderr, "F_OVERFLOW\n");
			break;
		case (F_UNDERFLOW):
			fprintf(stderr, "F_UNDERFLOW\n");
			break;
	}
}
