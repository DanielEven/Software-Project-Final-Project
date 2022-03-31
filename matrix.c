#include "matrix.h"

Matrix *alloc_matrix(int m, int n)
{
    int i;
    Matrix *to = malloc(sizeof(Matrix));
    if (!to)
    {
        return NULL;
    }

    to->m = m;
    to->n = n;
    to->vals = calloc(m, sizeof(double *));
    if (!to->vals)
    {
        free(to);
        return NULL;
    }
    for (i = 0; i < m; i++)
    {
        to->vals[i] = calloc(n, sizeof(double));
        if (!to->vals[i])
        {
            to->m = i - 1;
            free_matrix(to);
            return NULL;
        }
    }
    return to;
}
void free_matrix(Matrix *a)
{
    int i;
    if (a == NULL)
        return;
    
    for (i = 0; i < a->m; i++)
        free(a->vals[i]);
    free(a->vals);
    free(a);
}

Matrix *dup_matrix(Matrix *a)
{
    int i, j;
    Matrix *to;

    to = alloc_matrix(a->m, a->n);
    if (to == NULL)
        return to;
    for (i = 0; i < a->m; i++)
        for (j = 0; j < a->n; j++)
            to->vals[i][j] = a->vals[i][j];
    return to;
}
Matrix *matrix_from_arr(double **arr, int m, int n)
{
    int i, j;
    Matrix *to;

    to = alloc_matrix(m, n);
    if (to == NULL)
        return to;
    for (i = 0; i < m; i++)
        for (j = 0; j < n; j++)
            to->vals[i][j] = arr[i][j];
    return to;
}
Matrix *matrix_from_PyList(PyObject *lst)
{
    Matrix *to;
    Py_ssize_t i, j, m, n;

    m = PyList_Size(lst);
    n = PyList_Size(PyList_GET_ITEM(lst, 0));
    to = alloc_matrix((int)m, (int)n);
    if (to == NULL)
        return to;

    for (i = 0; i < m; i++)
    {
        for (j = 0; j < n; j++)
        {
            to->vals[i][j] = PyFloat_AsDouble(PyList_GetItem(PyList_GetItem(lst, i), j));
        }
    }
    return to;
}

Matrix *add_matrix(Matrix *a, Matrix *b)
{
    int i, j;
    Matrix *res;

    assert(SAME_SIZE(a, b));
    res = alloc_matrix(a->m, a->n);
    if (res == NULL)
        return res;
    for (i = 0; i < a->m; i++)
        for (j = 0; j < a->n; j++)
            res->vals[i][j] = a->vals[i][j] + b->vals[i][j];

    return res;
}

void add_matrix_inp(Matrix *a, Matrix *b)
{
    int i, j;

    assert(SAME_SIZE(a, b));
    for (i = 0; i < a->m; i++)
        for (j = 0; j < a->n; j++)
            a->vals[i][j] += b->vals[i][j];
}

Matrix *sub_matrix(Matrix *a, Matrix *b)
{
    int i, j;
    Matrix *res;

    assert(SAME_SIZE(a, b));
    res = alloc_matrix(a->m, a->n);
    if (res == NULL)
        return res;
    for (i = 0; i < a->m; i++)
        for (j = 0; j < a->n; j++)
            res->vals[i][j] = a->vals[i][j] - b->vals[i][j];

    return res;
}

void sub_matrix_inp(Matrix *a, Matrix *b)
{
    int i, j;

    assert(SAME_SIZE(a, b));
    for (i = 0; i < a->m; i++)
        for (j = 0; j < a->n; j++)
            a->vals[i][j] -= b->vals[i][j];
}

Matrix *dot_matrix(Matrix *a, Matrix *b)
{
    int i, j, k;
    Matrix *res;

    assert(GOOD_FOR_DOT(a, b));
    res = alloc_matrix(a->m, b->n);
    if (res == NULL)
        return res;
    for (i = 0; i < a->m; i++)
        for (j = 0; j < b->n; j++)
            for (k = 0; k < a->n; k++)
                res->vals[i][j] += a->vals[i][k] * b->vals[k][j];

    return res;
}

Matrix *mult_matrix(Matrix *a, double scalar)
{
    int i, j;
    Matrix *res;

    res = alloc_matrix(a->m, a->n);
    if (res == NULL)
        return res;
    for (i = 0; i < a->m; i++)
        for (j = 0; j < a->n; j++)
            res->vals[i][j] = a->vals[i][j] * scalar;

    return res;
}

void mult_matrix_inp(Matrix *a, double scalar)
{
    int i, j;

    for (i = 0; i < a->m; i++)
        for (j = 0; j < a->n; j++)
            a->vals[i][j] *= scalar;
}

Matrix *pow_diag_matrix(Matrix *a, double alpha)
{
    int i;
    Matrix *res;

    res = alloc_matrix(a->m, a->n);
    if (res == NULL)
        return res;
    for (i = 0; i < a->m; i++)
        res->vals[i][i] = pow(a->vals[i][i], alpha);

    return res;
}

void pow_diag_matrix_inp(Matrix *a, double alpha)
{
    int i;

    for (i = 0; i < a->m; i++)
        a->vals[i][i] = pow(a->vals[i][i], alpha);
}

Matrix *transpose_matrix(Matrix *a)
{
    int i, j;
    Matrix *res;

    res = alloc_matrix(a->n, a->m);
    if (res == NULL)
        return res;
    for (i = 0; i < a->n; i++)
        for (j = 0; j < a->m; j++)
            res->vals[i][j] = a->vals[j][i];

    return res;
}

Matrix *get_identity(int n)
{
    int i;
    Matrix *to = alloc_matrix(n, n);
    if (to == NULL)
        return to;

    for (i = 0; i < n; i++)
        to->vals[i][i] = 1;

    return to;
}

int is_diag(Matrix *a)
{
    int i, j;
    assert(IS_SQUARE(a));

    for (i = 0; i < a->m; i++)
    {
        for (j = 0; j < a->n; j++)
        {
            if ((i != j) && (a->vals[i][j] != 0))
                return 0;
        }
    }
    return 1;
}

double off_sqr_of_sym_matrix(Matrix *A)
{
    double sum = 0;
    int i, j;
    for (i = 0; i < A->m; i++)
    {
        for (j = i + 1; j < A->n; j++)
            sum += 2 * pow(A->vals[i][j], 2);
    }
    return sum;
}
