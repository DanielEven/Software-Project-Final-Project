#include "DDmatrix.h"

Matrix *Create_DD_matrix(Matrix *WAmatrix)
{
    int i, z;
    Matrix *res;
    res = alloc_matrix(WAmatrix->m, WAmatrix->m);

    for (i = 0; i < WAmatrix->m; i++)
    {
        for (z = 0; z < WAmatrix->n; z++)
        {
            res->vals[i][i] += WAmatrix->vals[i][z];
        }
    }

    return res;
}