#include "NGLmatrix.h"

Matrix *create_DD_matrix(Matrix *WAmatrix)
{
    int i, z;
    Matrix *res;
    res = alloc_matrix(WAmatrix->m, WAmatrix->m);
    if (res == NULL)
        return res;

    for (i = 0; i < WAmatrix->m; i++)
    {
        for (z = 0; z < WAmatrix->n; z++)
        {
            res->vals[i][i] += WAmatrix->vals[i][z];
        }
    }

    return res;
}

Matrix *create_NGL_matrix(Matrix *WAmatrix, Matrix *DDmatrix)
{
    Matrix *res, *tmp1, *tmp2, *inv_sqrt_DDmatrix;

    res = get_identity(DDmatrix->m);
    if (res == NULL)
        return res;

    inv_sqrt_DDmatrix = pow_diag_matrix(DDmatrix, -0.5);
    if (inv_sqrt_DDmatrix == NULL)
        return inv_sqrt_DDmatrix;
    tmp1 = dot_matrix(inv_sqrt_DDmatrix, WAmatrix);
    if (tmp1 == NULL)
    {
        free_matrix(inv_sqrt_DDmatrix);
        return tmp1;
    }
    tmp2 = dot_matrix(tmp1, inv_sqrt_DDmatrix);
    if (tmp2 == NULL){
        free_matrix(inv_sqrt_DDmatrix);
        free_matrix(tmp1);
        return tmp2;
    }

    sub_matrix_inp(res, tmp2);

    free_matrix(tmp1);
    free_matrix(tmp2);
    free_matrix(inv_sqrt_DDmatrix);

    return res;
}