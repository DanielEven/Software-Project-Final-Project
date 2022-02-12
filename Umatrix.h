#ifndef U_MATRIX_H
#define U_MATRIX_H

#include "matrix.h"
#include <float.h>

#define SIGN(x) (((x) >= 0) * 2 - 1)

/* A function which calculates the eigenvectors and eigenvalues using the jacobi algorithm and Eigengap Heuristic.
The function returns a matrix with the k eigenvectors with the lowest eigenvalues of the Normalized Graph Laplacian matrix.
*/
Matrix *create_k_eigenvectors_matrix(Matrix *NGL);

/* A function to create the rotation matrix P from the matrix A. */
Matrix *create_rotation_matrix(Matrix *A);

/* A function to calculate A_tag as:
A_tag = (P^t) * A * P
*/
Matrix *transform_A(Matrix *A, Matrix *P);

/* Getting the pivot from A as Index. */
Index get_pivot_index(Matrix *A);

/* Calculating the theta from the matrix A and pivot index ind. */
double get_theta(Matrix *A, Index ind);

/* Calculating t from theta. */
double get_t(double theta);

/* Calculating c from t. */
double get_c(double t);

/* Checking the convergance of the algorithm. */
int has_converged(Matrix *A, Matrix *A_tag);

/* Creating a struct for a pair: eigenvectors, eigenvalues.*/
typedef struct Eigen_Pair
{
    double *vect;
    double val;
} Eigen_Pair;

/* Create Eigen_Pair array. */
Eigen_Pair *get_Eigen_Pair_arr(Matrix *values, Matrix *vects);

/* Compare btween 2 Eigen_Pairs. */
int cmp_Eigen_Pair(const void *a, const void *b);

/* Creating a matrix from the first k eigenvectors as columns.
n is the vector length.
*/
Matrix *create_matrix_from_k_Eigen_Pair(Eigen_Pair *pairs, int k, int n);

#endif