#ifndef MATRIX_H
#define MATRIX_H

#include <stdlib.h>

#define PY_SSIZE_T_CLEAN
#include <Python.h>

/* Defining the matrix struct. */
typedef struct Matrix
{
    double **vals;
    int m;
    int n;
} Matrix;

/* Matrix memory management. */
Matrix alloc_matrix(int m, int n);
void free_matrix(Matrix a);

/* Creating a matrix.*/
Matrix dup_matrix(Matrix a);
Matrix matrix_from_arr(double **arr, int m, int n);
Matrix matrix_from_PyList(PyObject *lst);

/* Operations over matrices. 
Every function has 2 versions:
1. An in place version - inp.
2. A vestion with a result parameter.
*/
void add_matrix(Matrix res, Matrix a, Matrix b);
void add_matrix_inp(Matrix a, Matrix b);

void sub_matrix(Matrix res, Matrix a, Matrix b);
void sub_matrix_inp(Matrix a, Matrix b);

void dot_matrix(Matrix res, Matrix a, Matrix b);

void mult_matrix(Matrix res, Matrix a, double scalar);
void mult_matrix_inp(Matrix a, double scalar);

#endif