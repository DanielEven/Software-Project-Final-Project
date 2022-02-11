#include "Umatrix.h"

Matrix *Create_k_eigenvectors_matrix(Matrix *NGL)
{
    /* Declaring variables. */
    int iter_count = 0, n = NGL->n, i, k;
    double max_delta = DBL_MIN;
    Matrix *A = dup_matrix(NGL), *V = get_identity(NGL->m), *A_tag, *U;

    Eigen_Pair *pairs_arr;

    /* Jacobi algorithm. */
    do
    {
        Matrix *tmp, *P;

        P = create_rotation_matrix(A);
        A_tag = transform_A(A, P);

        tmp = dot_matrix(V, P);
        free_matrix(V);
        V = tmp;

        free_matrix(A);
        A = A_tag;

        free_matrix(P);
    } while (!has_converged(A, A_tag) || (++iter_count) >= 100);

    /* Ordering the eigenvalues and eigenvectors. */
    pairs_arr = get_Eigen_Pair_arr(A, V);
    qsort(pairs_arr, n, sizeof(Eigen_Pair), cmp_Eigen_Pair);

    /* Freeing the matrices. */
    free_matrix(A); /* We also took the eigenvalues. */
    free(V->vals);
    free(V);
    /* We are not freeing the pointers inside V->vals, because of the Eigen_Pair arr is using them. */

    /* Eigengap Heuristic. */
    for (i = 0; i < n / 2; i++)
    {
        double delta = abs(pairs_arr[i].val - pairs_arr[i + 1].val);
        if (delta > max_delta) /* Bigger, not equal. */
        {
            max_delta = delta;
            k = i;
        }
    }

    /* Create and return the U matrix. */
    U = create_matrix_from_k_Eigen_Pair(pairs_arr, k, n);

    /* Freeing variables. */
    for (i = k+1; i<n; i++)
        free(pairs_arr[i].vect);
    free(pairs_arr);

    return U;
}

Matrix *create_rotation_matrix(Matrix *A)
{
    Matrix *P = get_identity(A->m);
    Index ind = get_pivot_index(A);
    double theta = get_theta(A, ind);
    double t = get_t(theta);
    double c = get_c(t);
    double s = t * c;

    P->vals[ind.i][ind.j] = s;
    P->vals[ind.j][ind.i] = -s;
    P->vals[ind.i][ind.i] = c;
    P->vals[ind.j][ind.j] = c;

    return P;
}

Matrix *transform_A(Matrix *A, Matrix *P)
{
    Matrix *A_tag, *P_T, *tmp;
    P_T = transpose_matrix(P);

    tmp = dot_matrix(P_T, A);
    A_tag = dot_matrix(tmp, P);

    free_matrix(tmp);
    free_matrix(P_T);
    return A_tag;
}

Index get_pivot_index(Matrix *A)
{
    Index res;

    // TODO

    return res;
}

double get_theta(Matrix *A, Index ind)
{
    double nom, denom;

    nom = A->vals[ind.j][ind.j] - A->vals[ind.i][ind.i];
    denom = 2 * A->vals[ind.i][ind.j];

    return nom / denom;
}

double get_t(double theta)
{
    double denom = abs(theta) + sqrt(pow(theta, 2) + 1);

    return SIGN(theta) / denom;
}

double get_c(double t)
{
    double denom = sqrt(pow(t, 2) + 1);

    return 1 / denom;
}

int has_converged(Matrix *A, Matrix *A_tag)
{
    int res;

    // TODO

    return res;
}

Eigen_Pair *get_Eigen_Pair_arr(Matrix *values, Matrix *vects)
{
    int i;
    Eigen_Pair *res;
    res = calloc(vects->m, sizeof(Eigen_Pair));

    for (i = 0; i < vects->m; i++)
    {
        res[i].vect = vects->vals[i];
        res[i].val = values->vals[i][i];
    }

    return res;
}

int cmp_Eigen_Pair(const void *a, const void *b)
{
    return ((const Eigen_Pair *)a)->val - ((const Eigen_Pair *)b)->val;
}

Matrix *create_matrix_from_k_Eigen_Pair(Eigen_Pair *pairs, int k, int n)
{
    int i;
    double **arr = calloc(k, sizeof(double *));
    if (!arr)
    {
        /* TODO handle error.*/
    }

    for (i = 0; i < k; i++)
    {
        arr[i] = pairs[i].vect;
    }

    return matrix_from_arr(arr, k, n);
}