#ifndef MATRIX_H
#define MATRIX_H

#include <stdlib.h>
#include <assert.h>
#include <math.h>
#include <stdio.h>


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

/* Power the diagonal of a square matrix. */
Matrix *pow_diag_matrix(Matrix *a, double alpha);
void pow_diag_matrix_inp(Matrix *a, double alpha);

Matrix *transpose_matrix(Matrix *a);

/* A function to get I. */
Matrix *get_identity(int n);

/* A function to check if a matrix is diagonal. */
int is_diag(Matrix *a);

/* A function to calculate the squared off of a matrix, optimized for symmetric matrices */
double off_sqr_of_sym_matrix(Matrix *A);

/* Functions for printing matrices */
void print_matrix(Matrix *a);
void print_row(double *row, int n);

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