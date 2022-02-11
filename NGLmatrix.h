#ifndef NGL_MATRIX_H
#define NGL_MATRIX_H

#include "matrix.h"

/* A function which creates the Diagonal Degree Matrix from the Weighted Adjacency Matrix. */
Matrix *create_DD_matrix(Matrix *WAmatrix);

/* A function which creates the Normalized Graph Laplacian
from the Weighted Adjacency Matrix and Diagonal Degree Matrix. */
Matrix *create_NGL_matrix(Matrix *WAmatrix, Matrix *DDmatrix);

#endif
