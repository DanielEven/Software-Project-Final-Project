/* A file with function to handle vectors (double array).*/
#ifndef VECTOR_H
#define VECTOR_H

#include <math.h>
#include <stdlib.h>
#include <Python.h>

/* Euclidean norm calculation. */
double get_dist(double *v1, double *v2, int d);

/* Operations over vectors.
Every function has 2 versions:
1. An in place version - inp.
2. A version with a result parameter - which is allocated INSIDE the function.
*/
double *divide_vector(double *vect, double alpha, int n);
void divide_vector_inp(double *vect, double alpha, int n);

double *normalize_vector(double *vect, int n);
void normalize_vector_inp(double *vect, int n);

/* A function to sum the elements of a vector */
double sum_vector(double *vect, int n);

/* Vector array freeing. */
void free_vect_arr(double **v_lst, int num_of_vects);

/* Free the pointer arrays, from an arr of vect arr. */
void free_arr_of_vect_arr(double ***v_lst, int num_of_vects);

/* Make a PyObject from vector array and its sizes. */
PyObject *convert_vect_arr_to_PyObject(double **ptr, Py_ssize_t size, Py_ssize_t size_sub);

/* Convert a PyObject to a vector array. */
double **convert_PyObject_to_vect_arr(PyObject *lst, Py_ssize_t n, Py_ssize_t d);

#endif