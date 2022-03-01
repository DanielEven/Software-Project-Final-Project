#define PY_SSIZE_T_CLEAN
#include <Python.h>

#include "matrix.h"
#include "vector.h"
#include "WAmatrix.h"
#include "NGLmatrix.h"
#include "Umatrix.h"
#include "Tmatrix.h"

#include <string.h>

/* Afunction to calculate the result, by sending the data_matrix to the right function - according to goal. */
Matrix *calculate_requested(Matrix *data_matrix, Py_ssize_t k, const char *goal);

