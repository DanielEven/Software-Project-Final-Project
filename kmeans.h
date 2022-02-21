#include "Python.h"
#include <float.h>
#include "vector.h"

/* Function declarations. */
 double **kmeans(double **vect_arr, double **cents, Py_ssize_t n, Py_ssize_t k, Py_ssize_t d, Py_ssize_t max_iter, double eps);
 double ***assign_vetors(double **vect_arr, double **cents, Py_ssize_t n, Py_ssize_t k, Py_ssize_t d);
 int find_closest(double *vect, double **cents, Py_ssize_t k, Py_ssize_t d);
 double get_dist_sqr(double *v1, double *v2, Py_ssize_t d);
/*The vect_arr and old_cents is in order to free if there is a problem*/
 double **calculate_new_cents(double ***mapping, /*In order to free if there is a problem*/ double **vect_arr, double **old_cents, Py_ssize_t n, Py_ssize_t k, Py_ssize_t d);
/* The result should be returned through the sum parameter.*/
void vector_sum(double *sum, double **vectors, int len_lst, Py_ssize_t d);
 void devide_vector(double *vect, double alpha, Py_ssize_t d);
 int check_diff_cents_square(double **cents, double **new_cents, double eps_sqrd, Py_ssize_t k, Py_ssize_t d);
