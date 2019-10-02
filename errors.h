/*!
 * \file errors.h
 *
 * Definições para errors.c
 */
#include <stdio.h>
//error values
#define F_DIVBYZERO -1
#define F_INEXACT -2
#define F_INVALID -4
#define F_OVERFLOW -8
#define F_UNDERFLOW -16

//void print_error (int errnum, char *func_name, char *line);
void print_error (int errnum);
