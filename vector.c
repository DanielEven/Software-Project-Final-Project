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

double *divide_vector(double *vect, double alpha, int n)
{
    int i;
    double *res = calloc(n, sizeof(double));
    if (!res)
    {
        /* TODO handle error */
    }
    for (i = 0; i < n; i++)
    {
        res[i] = (vect[i] / alpha);
    }
    return res;
}

void divide_vector_inp(double *vect, double alpha, int n)
{
    int i;
    for (i = 0; i < n; i++)
    {
        vect[i] /= alpha;
    }
}

double *normalize_vector(double *vect, int n)
{
    double sum;
    sum = sum_vector(vect, n);
    return divide_vector(vect, sum, n);
}

void normalize_vector_inp(double *vect, int n)
{
    double sum;
    sum = sum_vector(vect, n);
    divide_vector_inp(vect, sum, n);
}

double sum_vector(double *vect, int n)
{
    int i;
    double sum = 0;
    for (i = 0; i < n; i++)
        sum += vect[i];
    return sum;
}

void free_vect_arr(double **v_lst, Py_ssize_t num_of_vects)
{
    int i;
    if (v_lst == NULL)
        return;
    for (i = 0; i < num_of_vects; i++)
    {
        free(v_lst[i]);
    }
    free(v_lst);
}

void free_arr_of_vect_arr(double ***ptr_list, Py_ssize_t num_of_vects)
{
    int k;
    if (ptr_list == NULL)
        return;
    for (k = 0; k < num_of_vects; k++)
    {
        free(ptr_list[k]);
    }
    free(ptr_list);
}

PyObject *convert_vect_arr_to_PyObject(double **ptr, Py_ssize_t size, Py_ssize_t size_sub)
{
    int i, j;
    PyObject *to = PyList_New(size);
    PyObject *sub;

    for (i = 0; i < size; i++)
    {
        sub = PyList_New(size_sub);
        for (j = 0; j < size_sub; j++)
            PyList_SetItem(sub, j, PyFloat_FromDouble(ptr[i][j]));

        PyList_SetItem(to, i, sub);
    }
    return to;
}

double **convert_PyObject_to_vect_arr(PyObject *lst, Py_ssize_t n, Py_ssize_t d)
{
    double **ptrs_list, *sub;
    Py_ssize_t i, j;
    if ((ptrs_list = calloc(sizeof(double *), n)) == NULL)
    {
        return NULL;
    }
    for (i = 0; i < n; i++)
    {
        if ((sub = calloc(sizeof(double *), d)) == NULL)
        {
            free_vect_arr(ptrs_list, i);
            return NULL;
        }
        for (j = 0; j < d; j++)
        {
            sub[j] = PyFloat_AsDouble(PyList_GetItem(PyList_GetItem(lst, i), j));
        }
        ptrs_list[i] = sub;
    }
    return ptrs_list;
}