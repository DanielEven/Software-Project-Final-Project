#include "vector.h"


double get_dist(double *v1, double *v2, int d)
{
    double sum = 0;
    int i = 0;
    for (i = 0; i < d; i++)
    {
        sum += (v1[i] - v2[i]) * (v1[i] - v2[i]);
    }

    return sqrt(sum);
}

void free_vect_arr(double **v_lst, int num_of_vects)
{
    int i;
    for (i = 0; i < num_of_vects; i++)
    {
        free(v_lst[i]);
    }
    free(v_lst);
}