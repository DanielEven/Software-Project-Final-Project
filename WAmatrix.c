#include "WAmatrix.h"

Matrix *Create_WA_matrix(Matrix *vects_rows)
{
    int i, j;
    Matrix *res;

    res = alloc_matrix(vects_rows->m, vects_rows->m);

    for (i = 0; i < vects_rows->m; i++)
    {
        for (j = 0; j < vects_rows->m; j++)
        {
            res->vals[i][j] = exp(-get_dist(vects_rows->vals[i], vects_rows->vals[j], vects_rows->n) / 2);
        }
    }

    return res;
}