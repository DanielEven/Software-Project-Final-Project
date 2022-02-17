#include <Python.h>

/* Afunction to calculate the result, by sending the data_matrix to the right function - according to goal. */
Matrix *calculate_requested(Matrix *data_matrix, Py_ssize_t, const char *goal);

/* Make a PyObject from array and its sizes. */
PyObject *convert_pointers_to_PyObject(double **ptr, Py_ssize_t size, Py_ssize_t size_sub);