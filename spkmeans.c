/* C Interface of the code.*/
/* Has a function to manage the calls to all of the C files. */
#include "spkmeans.h"

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