/* C Interface of the code.*/
/* Has a function to manage the calls to all of the C files. */

#include "spkmeans.h"

Matrix *calculate_requested(Matrix *data_matrix, Py_ssize_t k, const char *goal)
{
    Matrix *WA, *DD, *NGL;

    WA = create_WA_matrix(data_matrix);
    if (!strcmp(goal, "wam"))
    {
        return WA;
    }

    DD = create_DD_matrix(WA);
    if (!strcmp(goal, "ddg"))
    {
        free_matrix(WA);
        return DD;
    }

    NGL = create_NGL_matrix(WA, DD);
    free_matrix(WA);
    free_matrix(DD);

    if (!strcmp(goal, "lnorm"))
    {
        return NGL;
    }

    return NULL;
}
