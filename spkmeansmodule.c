/* Python C-API wrapper. Has the C-API module & function definitions. */
/* Also converts the data to matrix. (?).*/

#define PY_SSIZE_T_CLEAN /* For all # variants of unit formats (s#, y#, etc.) use Py_ssize_t rather than int. */
#include <Python.h>
#include "matrix.h"
#include "spkmeans.h"
#include "vector.h"

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

    matrix_result = calculate_requested(data_matrix, k, goal);

    /* Convert the result to Python list. */
    result = convert_pointers_to_PyObject(matrix_result->vals, matrix_result->m, matrix_result->n);

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

    data = convert_PyObject_to_pointers(data_lst, n, d);
    if (data == NULL)
    {
        ERROR("An Error Has Occurred");
    }
    cents = convert_PyObject_to_pointers(cents_lst, k, d);
    if (cents == NULL)
    {
        ERROR("An Error Has Occurred");
    }

    c_result = kmeans(data, cents, n, k, d, 300, 0);

    /* Convert the result to Python list. */
    result = convert_pointers_to_PyObject(c_result, k, d);

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
PyInit_mykmeanssp(void)
{
    PyObject *m;
    m = PyModule_Create(&moduledef);
    if (!m)
    {
        return NULL;
    }
    return m;
}
