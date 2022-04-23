#include "Umatrix.h"

Matrix *create_k_eigenvectors_matrix(Matrix *NGL, int k, int for_output_print)
{
    /* Declaring variables. */
    int iter_count = 0, n = NGL->n, i;
    double max_delta = -DBL_MAX;
    Eigen_Pair *pairs_arr;
    Matrix *A = dup_matrix(NGL), *V = get_identity(NGL->m), *A_tag, *U, *tr;

    if ((A == NULL) || (V == NULL))
    {
        free_matrix(A);
        free_matrix(V);
        return NULL;
    }

    /* Jacobi algorithm. */
    do
    {
        Matrix *tmp, *P;
        Index ind = get_pivot_index(A);

        P = create_rotation_matrix(A, ind);
        if (P == NULL)
        {
            free_matrix(A);
            free_matrix(V);
            return NULL;
        }
        A_tag = transform_A(A, P, ind);
        if (A_tag == NULL)
        {
            free_matrix(A);
            free_matrix(P);
            free_matrix(V);
            return A_tag;
        }

        tmp = dot_matrix(V, P);
        free_matrix(V);
        free_matrix(P);
        V = tmp;
        if (V == NULL)
        {
            free_matrix(A);
            free_matrix(A_tag);
            return V;
        }

        /* Check convergence. */
        if (has_converged(A, A_tag))
        {
            free_matrix(A);
            A = A_tag;
            break;
        }
        free_matrix(A);
        A = A_tag;

    } while ((++iter_count) < 100);

    /* Extract the eigenvalues and eigenvectors. */
    tr = transpose_matrix(V);
    free_matrix(V);
    V = tr;
    pairs_arr = get_Eigen_Pair_arr(A, V);

    if (pairs_arr == NULL)
    {
        free_matrix(A);
        free_matrix(V);
        return NULL;
    }

    /* Ordering the eigenvalues and eigenvectors. */

    if (for_output_print)
    {
        U = create_matrix_from_k_Eigen_Pair(pairs_arr, n, n, 1);
    }
    else
    {
        qsort(pairs_arr, n, sizeof(Eigen_Pair), cmp_Eigen_Pair);

        if (k == 0)
        {
            /* Eigengap Heuristic. */
            for (i = 0; i < n / 2; i++)
            {
                double delta = fabs(pairs_arr[i].val - pairs_arr[i + 1].val);
                if (delta > max_delta) /* Bigger, not equal. */
                {
                    max_delta = delta;
                    k = i + 1;
                }
            }
        }
        if (k == 1)
        {
            U = NULL; /* Can't apply kmeans. */
        }
        else
        {
            /* Create and return the U matrix. */
            U = create_matrix_from_k_Eigen_Pair(pairs_arr, k, n, 0);
        }
    }

    /* Freeing the variables. */
    free(pairs_arr); /* We are not freeing the pointers to the vectors, because the they are in V. */
    free_matrix(A);  /* We already took the eigenvalues. */
    free_matrix(V);

    return U;
}

Matrix *create_rotation_matrix(Matrix *A, Index ind)
{
    double theta = get_theta(A, ind);
    double t = get_t(theta);
    double c = get_c(t);
    double s = t * c;
    Matrix *P = get_identity(A->m);
    if (P == NULL)
        return P;

    P->vals[ind.i][ind.j] = s;
    P->vals[ind.j][ind.i] = -s;
    P->vals[ind.i][ind.i] = c;
    P->vals[ind.j][ind.j] = c;

    return P;
}

Matrix *transform_A(Matrix *A, Matrix *P, Index ind)
{
    Matrix *A_tag, *P_T, *tmp;
    int r, i = ind.i, j = ind.j;
    double s = P->vals[i][j], c = P->vals[i][i];

    A_tag = dup_matrix(A);

    for (r = 0; r < A->m; r++)
    {
        if ((r != i) && (r != j))
        {
            A_tag->vals[r][i] = c * A->vals[r][i] - s * A->vals[r][j];
        }
    }

    for (r = 0; r < A->m; r++)
    {
        if ((r != i) && (r != j))
        {
            A_tag->vals[r][j] = c * A->vals[r][j] + s * A->vals[r][i];
        }
    }

    A_tag->vals[i][i] = c * c * A->vals[i][i] + s * s * A->vals[j][j] - 2 * s * c * A->vals[i][j];

    A_tag->vals[j][j] = s * s * A->vals[i][i] + c * c * A->vals[j][j] + 2 * s * c * A->vals[i][j];

    return A_tag;
}

Index get_pivot_index(Matrix *A)
{
    int row, col;
    double max_val = -DBL_MAX;
    Index res;
    for (row = 0; row < A->m; row++)
    {
        for (col = row + 1; col < A->n; col++)
        {
            if (fabs(A->vals[row][col]) > max_val)
            {
                max_val = fabs(A->vals[row][col]);
                res.i = row;
                res.j = col;
            }
        }
    }
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
    double denom = fabs(theta) + sqrt(pow(theta, 2) + 1);

    return SIGN(theta) / denom;
}

double get_c(double t)
{
    double denom = sqrt(pow(t, 2) + 1);

    return 1 / denom;
}

int has_converged(Matrix *A, Matrix *A_tag)
{
    const double eps = 1.0 * pow(10, -5);
    return (off_sqr_of_sym_matrix(A) - off_sqr_of_sym_matrix(A_tag)) <= eps;
}

Eigen_Pair *get_Eigen_Pair_arr(Matrix *values, Matrix *vects)
{
    int i;
    Eigen_Pair *res;
    res = calloc(vects->m, sizeof(Eigen_Pair));
    if (res == NULL)
        return res;

    for (i = 0; i < vects->m; i++)
    {
        res[i].vect = vects->vals[i];
        res[i].val = values->vals[i][i];
    }

    return res;
}

int cmp_Eigen_Pair(const void *a, const void *b)
{
    double v1 = ((const Eigen_Pair *)a)->val;
    double v2 = ((const Eigen_Pair *)b)->val;
    if (v1 > v2)
        return 1;
    else if (v1 < v2)
        return -1;
    return 0;
}

Matrix *create_matrix_from_k_Eigen_Pair(Eigen_Pair *pairs, int k, int n, int include_vals)
{
    int i, j;
    double **arr = calloc(n + !!include_vals, sizeof(double *));
    Matrix *to;

    if (!arr)
    {
        return NULL;
    }

    if (include_vals)
    {
        arr[0] = calloc(k, sizeof(double));
        if (!(arr[0]))
        {
            free(arr);
            return NULL;
        }
        for (j = 0; j < k; j++)
        {
            arr[0][j] = pairs[j].val;
        }
    }

    for (i = 0 + !!include_vals; i < n + !!include_vals; i++)
    {
        arr[i] = calloc(k, sizeof(double));
        if (!(arr[i]))
        {
            free_vect_arr(arr, i - 1);
            return NULL;
        }
        for (j = 0; j < k; j++)
            arr[i][j] = pairs[j].vect[i - !!include_vals]; /* The vectors are the columns. */
    }
    to = matrix_from_arr(arr, n + !!include_vals, k);
    free_vect_arr(arr, n + !!include_vals);

    return to;
}