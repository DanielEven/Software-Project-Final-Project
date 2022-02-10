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