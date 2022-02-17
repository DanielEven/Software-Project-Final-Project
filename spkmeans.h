#include <Python.h>
#include "matrix.h"

/* Afunction to calculate the result, by sending the data_matrix to the right function - according to goal. */
Matrix *calculate_requested(Matrix *data_matrix, Py_ssize_t k, const char *goal);

/* Make a PyObject from pointer array and its sizes. */
PyObject *convert_pointers_to_PyObject(double **ptr, Py_ssize_t size, Py_ssize_t size_sub);

/* Convert a PyObject to a pointer array. */
double **convert_PyObject_to_pointers(PyObject *lst, Py_ssize_t n, Py_ssize_t d);
