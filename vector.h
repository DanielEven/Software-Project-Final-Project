/* A file with function to handle vectors (double array).*/
#ifndef VECTOR_H
#define VECTOR_H

#include <math.h>
#include <stdlib.h>

/* Euclidean norm calculation. */
double get_dist(double *v1, double *v2, int d);

/* Vector array freeing. */
void free_vect_arr(double **v_lst, int num_of_vects);

#endif