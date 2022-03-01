/* C Interface of the code.*/
/* Has a function to manage the calls to all of the C files. */

#include "spkmeans.h"

Matrix *calculate_requested(Matrix *data_matrix, Py_ssize_t k, const char *goal)
{
    Matrix *WA, *DD, *NGL, *U, *T;

    WA = create_WA_matrix(data_matrix);
    if (!strcmp(goal, "wam"))
    {
        return WA;
    }

    DD = create_DD_matrix(WA);
    if (!strcmp(goal, "ddg"))
    {
        free_matrix(WA);
        /* TODO pow_diag_matrix_inp(DD, -0.5); - this outputs DD^-1/2 like in the project_clarification.docx file*/
        return DD;
    }

    NGL = create_NGL_matrix(WA, DD);
    free_matrix(WA);
    free_matrix(DD);

    if (!strcmp(goal, "lnorm"))
    {
        return NGL;
    }

    if (!strcmp(goal, "jacobi"))
    {
        U = create_k_eigenvectors_matrix(NGL, (int)k, 1);
        free_matrix(NGL);
        /* TODO in the project_clarification.docx file the eigenvectors are the rows so we might need to transpose*/
        return U;
    }

    if (!strcmp(goal, "spk"))
    {
        U = create_k_eigenvectors_matrix(NGL, (int)k, 0);
        free_matrix(NGL);
        T = get_row_normalized_matrix(U);
        free_matrix(U);
        return T;
    }

    return NULL;
}
