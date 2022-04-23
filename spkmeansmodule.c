/* Python C-API wrapper. Has the C-API module & function definitions. */
/* Also converts the data to matrix. (?).*/

#define PY_SSIZE_T_CLEAN /* For all # variants of unit formats (s#, y#, etc.) use Py_ssize_t rather than int. */
#include <Python.h>

#include "matrix.h"
#include "vector.h"

#include "spkmeans.h"
#include "kmeans.h"

#define MAX_ITER 300
#define EPSILON 0

/* A helper method to create matrix from python list. */
Matrix *matrix_from_PyList(PyObject *lst);

/* Make a PyObject from vector array and its sizes. */
PyObject *convert_vect_arr_to_PyObject(double **ptr, Py_ssize_t size, Py_ssize_t size_sub);

/* Convert a PyObject to a vector array. */
double **convert_PyObject_to_vect_arr(PyObject *lst, Py_ssize_t n, Py_ssize_t d);

/* C Export - From the lecture. */

/*
 * This actually defines the  function using a wrapper C API function
 * The wrapping function needs a PyObject* self argument.
 * This is a requirement for all functions and methods in the C API.
 * It has input PyObject *args from Python.
 */
static PyObject *process_data_for_spectral_clustering_capi(PyObject *self, PyObject *args)
{
    /* Define args*/
    PyObject *data_lst = NULL, *result = NULL, *to = NULL;
    Py_ssize_t k;
    const char *goal;
    Matrix *data_matrix, *matrix_result;

    /* This parses the Python arguments*/
    if (!PyArg_ParseTuple(args, "Ons", &data_lst, &k, &goal))
    {
        return NULL; /* In the CPython API, a NULL value is never valid for a
                        PyObject* so it is used to signal that an error has occurred. */
    }

    if (!PyList_Check(data_lst))
        return NULL;

    data_matrix = matrix_from_PyList(data_lst);
    if (data_matrix == NULL)
        return NULL;

    matrix_result = calculate_requested(data_matrix, k, goal);
    if (matrix_result == NULL)
    {
        return NULL;
    }

    /* Convert the result to Python list. */
    result = convert_vect_arr_to_PyObject(matrix_result->vals, matrix_result->m, matrix_result->n);

    /* Free everything. */
    free_matrix(data_matrix);
    free_matrix(matrix_result);

    to = Py_BuildValue("O", result); /*  Py_BuildValue(...) returns a PyObject*  */
    Py_DecRef(to);
    return to;
}

static PyObject *kmeans_capi(PyObject *self, PyObject *args)
{
    /* Define args*/
    PyObject *data_lst = NULL, *cents_lst = NULL, *result, *to;

    double **data, **cents, **c_result;

    Py_ssize_t n, d, k;

    /* This parses the Python arguments*/
    if (!PyArg_ParseTuple(args, "OO", &data_lst, &cents_lst))
    {
        return NULL; /* In the CPython API, a NULL value is never valid for a
                        PyObject* so it is used to signal that an error has occurred. */
    }

    if (!PyList_Check(data_lst) || !PyList_Check(cents_lst))
        return NULL;

    n = PyList_Size(data_lst);
    d = PyList_Size(PyList_GetItem(data_lst, 0));
    k = PyList_Size(cents_lst);

    data = convert_PyObject_to_vect_arr(data_lst, n, d);
    if (data == NULL)
    {
        return NULL;
    }
    cents = convert_PyObject_to_vect_arr(cents_lst, k, d);
    if (cents == NULL)
    {
        return NULL;
    }

    c_result = kmeans(data, cents, n, k, d, MAX_ITER, EPSILON);

    /* Convert the result to Python list. */
    result = convert_vect_arr_to_PyObject(c_result, k, d);

    /* Free everything. */
    free_vect_arr(c_result, k);

    to = Py_BuildValue("O", result); /*  Py_BuildValue(...) returns a PyObject*  */
    Py_DecRef(to);
    return to;
}

/* This array tells Python what methods this module has. */
static PyMethodDef capiMethods[] = {

    {"process_data_for_spectral_clustering",                                                                     /* the Python method name that will be used */
     (PyCFunction)process_data_for_spectral_clustering_capi,                                                     /* the C-function that implements the Python function and returns static PyObject*  */
     METH_VARARGS,                                                                                               /* flags indicating parameters accepted for this function */
     PyDoc_STR("Use the Normalized Spectral Clustering Algorithm in order to make the data ready for kmeans.")}, /*  The docstring for the function */

    {"kmeans",                                              /* the Python method name that will be used */
     (PyCFunction)kmeans_capi,                              /* the C-function that implements the Python function and returns static PyObject*  */
     METH_VARARGS,                                          /* flags indicating parameters accepted for this function */
     PyDoc_STR("Implementation of the kmeans algorithm.")}, /*  The docstring for the function */

    {NULL, NULL, 0, NULL} /* The last entry must be all NULL as shown to act as asentinel. */
                          /* Python looks for this entry to know that allof the functions for the module have been defined. */
};

/* This initiates the module using the above definitions. */
static struct PyModuleDef moduledef = {
    PyModuleDef_HEAD_INIT,
    "spkmeansmoule", /* name of module */
    NULL,            /* module documentation, may be NULL */
    -1,              /* size of per-interpreter state of the module, or -1 if the module keeps state in global variables. */
    capiMethods      /* the PyMethodDef array from before containing the methods of the extension */
};

/*
 * The PyModuleDef structure, in turn, must be passed to the interpreter in the module’s initialization function.
 * The initialization function must be named PyInit_name(), where name is the name of the module and should match
 * what we wrote in struct PyModuleDef.
 * This should be the only non-static item defined in the module file
 */
PyMODINIT_FUNC
PyInit_spkmeansmodule(void)
{
    PyObject *m;
    m = PyModule_Create(&moduledef);
    if (!m)
    {
        return NULL;
    }
    return m;
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