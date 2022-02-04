#include "matrix.h"

Matrix alloc_matrix(int m, int n)
{
    int i;
    Matrix to;

    to.m = m;
    to.n = n;
    to.vals = calloc(m, sizeof(double *));
    for (int i = 0; i < m; i++)
    {
        to.vals[i] = calloc(n, sizeof(double));
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

Matrix copy_matrix(Matrix a)
{
    int i, j;
    Matrix to;

    to = alloc_matrix(a.m, a.n);
    for (i = 0; i < a.m; i++)
        for (j = 0; j < a.n; j++)
            to.vals[i][j] = a.vals[i][j];
    return to;
}
Matrix matrix_from_arr(int **arr, int m, int n)
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

void add_matrix(Matrix res, Matrix a, Matrix b) {}
void add_matrix_inp(Matrix a, Matrix b) {}

void sub_matrix(Matrix res, Matrix a, Matrix b) {}
void sub_matrix_inp(Matrix a, Matrix b) {}

void dot_matrix(Matrix res, Matrix a, Matrix b) {}
void dot_matrix_inp(Matrix a, Matrix b) {}

void mul_matrix(Matrix res, Matrix a, double scalar) {}
void mul_matrix_inp(Matrix a, double scalar) {}