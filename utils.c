/*!
 * \file utils.c
 * 
 * Utilidades que não se encaixam em categorias específicas
 */
#include "utils.h"

/*!
 * \brief Computa tempo real em que foi chamada
 *
 * \return Tempo computado
 */
double timestamp (void) {
	struct timeval tp;
	gettimeofday(&tp, NULL);
	return ((double)(tp.tv_sec*1000.0 + tp.tv_usec/1000.0));
}
