#ifndef MATRIX_H
#define MATRIX_H

#include <stdlib.h>
#include <assert.h>
#include <math.h>

#include <Python.h>

/* Defining the matrix struct. */
typedef struct Matrix
{
    double **vals;
    int m;
    int n;
} Matrix;

/* Matrix memory management. */
Matrix *alloc_matrix(int m, int n);
void free_matrix(Matrix *a);

/* Creating a matrix.*/
Matrix *dup_matrix(Matrix *a);
Matrix *matrix_from_arr(double **arr, int m, int n);
Matrix *matrix_from_PyList(PyObject *lst);

/* Operations over matrices.
Every function has 2 versions:
1. An in place version - inp.
2. A version with a result parameter - which is allocated INSIDE the function.
*/
Matrix *add_matrix(Matrix *a, Matrix *b);
void add_matrix_inp(Matrix *a, Matrix *b);

Matrix *sub_matrix(Matrix *a, Matrix *b);
void sub_matrix_inp(Matrix *a, Matrix *b);

Matrix *dot_matrix(Matrix *a, Matrix *b);

Matrix *mult_matrix(Matrix *a, double scalar);
void mult_matrix_inp(Matrix *a, double scalar);

Matrix *pow_elem_matrix(Matrix *a, double alpha);
void pow_elem_matrix_inp(Matrix *a, double alpha);

Matrix *transpose_matrix(Matrix *a);

/* A function to get I. */
Matrix *get_identity(int n);

/* A function to check if a matrix is diagonal. */
int is_diag(Matrix *a);

/* Size checking macros.*/
#define SAME_SIZE(a, b) ((((a)->m) == ((b)->m)) && (((a)->n) == ((b)->n)))
#define GOOD_FOR_DOT(a, b) (((a)->n) == ((b)->m))
#define IS_SQUARE(a) (((a)->m) == ((a)->n))

/* Defining the Index struct. */
typedef struct Index
{
    int i;
    int j;
} Index;

#endif