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

double *divide_vector(double *vect, double alpha, int n)
{
    int i;
    double *res = calloc(n, sizeof(double));
    if (!res)
    {
        /* TODO handle error */
    }
    for (i = 0; i < n; i++)
    {
        res[i] = (vect[i] / alpha);
    }
    return res;
}

void divide_vector_inp(double *vect, double alpha, int n)
{
    int i;
    for (i = 0; i < n; i++)
    {
        vect[i] /= alpha;
    }
}

double *normalize_vector(double *vect, int n){
    int sum;
    sum = sum_vector(vect, n);
    return divide_vector(vect, sum, n);
}

void normalize_vector_inp(double *vect, int n){
    int sum;
    sum = sum_vector(vect, n);
    divide_vector_inp(vect, sum, n);
}

double sum_vector(double *vect, int n)
{
    int i;
    double sum = 0;
    for (i = 0; i < n; i++)
        sum += vect[i];
    return sum;
}
