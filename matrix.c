#include "matrix.h"

Matrix alloc_matrix(int m, int n)
{
    int i;
    Matrix to;

    to.m = m;
    to.n = n;
    to.vals = calloc(m, sizeof(double *));
    if (!to.vals)
    {
        /* TODO handle error.*/
    }
    for (i = 0; i < m; i++)
    {
        to.vals[i] = calloc(n, sizeof(double));
        if (!to.vals[i])
        {
            /* TODO handle error.*/
        }
    }
    return to;
}
void free_matrix(Matrix a)
{
    int i;

    for (i = 0; i < a.m; i++)
        free(a.vals[i]);
    free(a.vals);
}

Matrix dup_matrix(Matrix a)
{
    int i, j;
    Matrix to;

    to = alloc_matrix(a.m, a.n);
    for (i = 0; i < a.m; i++)
        for (j = 0; j < a.n; j++)
            to.vals[i][j] = a.vals[i][j];
    return to;
}
Matrix matrix_from_arr(double **arr, int m, int n)
{
    int i, j;
    Matrix to;

    to = alloc_matrix(m, n);
    for (i = 0; i < m; i++)
        for (j = 0; j < n; j++)
            to.vals[i][j] = arr[i][j];
    return to;
}
Matrix matrix_from_PyList(PyObject *lst)
{
    Matrix to;
    Py_ssize_t i, j, m, n;

    m = PyList_Size(lst);
    n = PyList_Size(PyList_GET_ITEM(lst, 0));
    to = alloc_matrix(m, n);

    for (i = 0; i < m; i++)
    {
        for (j = 0; j < n; j++)
        {
            to.vals[i][j] = PyFloat_AsDouble(PyList_GetItem(PyList_GetItem(lst, i), j));
        }
    }
    return to;
}

void add_matrix(Matrix res, Matrix a, Matrix b)
{
    int i, j;

    assert(SAME_SIZE(a, b));
    res = alloc_matrix(a.m, a.n);
    for (i = 0; i < a.m; i++)
        for (j = 0; j < a.n; j++)
            res.vals[i][j] = a.vals[i][j] + b.vals[i][j];
}
void add_matrix_inp(Matrix a, Matrix b)
{
    int i, j;

    assert(SAME_SIZE(a, b));
    for (i = 0; i < a.m; i++)
        for (j = 0; j < a.n; j++)
            a.vals[i][j] += b.vals[i][j];
}

void sub_matrix(Matrix res, Matrix a, Matrix b)
{
    int i, j;

    assert(SAME_SIZE(a, b));
    res = alloc_matrix(a.m, a.n);
    for (i = 0; i < a.m; i++)
        for (j = 0; j < a.n; j++)
            res.vals[i][j] = a.vals[i][j] - b.vals[i][j];
}
void sub_matrix_inp(Matrix a, Matrix b)
{
    int i, j;

    assert(SAME_SIZE(a, b));
    for (i = 0; i < a.m; i++)
        for (j = 0; j < a.n; j++)
            a.vals[i][j] -= b.vals[i][j];
}

void dot_matrix(Matrix res, Matrix a, Matrix b)
{
    int i, j, k;

    assert(GOOD_FOR_DOT(a, b));
    res = alloc_matrix(a.m, b.n);
    for (i = 0; i < a.m; i++)
        for (j = 0; j < b.n; j++)
            for (k = 0; k < a.n; k++)
                res.vals[i][j] = a.vals[i][k] * b.vals[k][j];
}

void mult_matrix(Matrix res, Matrix a, double scalar)
{
    int i, j;

    res = alloc_matrix(a.m, a.n);
    for (i = 0; i < a.m; i++)
        for (j = 0; j < a.n; j++)
            res.vals[i][j] = a.vals[i][j] * scalar;
}
void mult_matrix_inp(Matrix a, double scalar)
{
    int i, j;

    for (i = 0; i < a.m; i++)
        for (j = 0; j < a.n; j++)
            a.vals[i][j] *= scalar;
}