#include "Python.h"
#include <float.h>
#include "vector.h"

/* Function declarations. */
static double **kmeans(double **vect_arr, double **cents, Py_ssize_t max_iter, double eps);
static double ***assign_vetors(double **vect_arr, double **cents);
static int find_closest(double *vect, double **cents);
static double get_dist_sqr(double *v1, double *v2);
/*The vect_arr and old_cents is in order to free if there is a problem*/
static double **calculate_new_cents(double ***mapping, double **vect_arr, double **old_cents);
/* The result should be returned through the sum parameter.*/
static void vector_sum(double *sum, double **vectors, int len_lst);
static void devide_vector(double *vect, double alpha);
static int check_diff_cents_square(double **cents, double **new_cents, double eps_sqrd);