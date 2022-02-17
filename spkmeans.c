/* C Interface of the code.*/
/* Has a function to manage the calls to all of the C files. */

#include "spkmeans.h"
#include "vector.h"

Matrix *calculate_requested(Matrix *data_matrix, Py_ssize_t k, const char *goal)
{
    return NULL;
}

PyObject *convert_pointers_to_PyObject(double **ptr, Py_ssize_t size, Py_ssize_t size_sub)
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

double **convert_PyObject_to_pointers(PyObject *lst, Py_ssize_t n, Py_ssize_t d)
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