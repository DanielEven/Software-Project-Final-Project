#ifndef WA_MATRIX_H
#define WA_MATRIX_H

#include "matrix.h"
#include "vector.h"

/* A function which creates the weighted adjacency matrix from
the vectors - they are the rows of vects_rows. */
Matrix *Create_WA_matrix(Matrix *vects_rows);

#endif
