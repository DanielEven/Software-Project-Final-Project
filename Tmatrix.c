#include "Tmatrix.h"

Matrix *get_row_normalized_matrix(Matrix *U)
{
    int i;
    Matrix *T;

    T = alloc_matrix(U->m, U->n);
    if (T == NULL)
        return T;

    for (i = 0; i < U->m; i++)
    {
        T->vals[i] = normalize_vector(U->vals[i], U->n);
    }

    return T;
}
