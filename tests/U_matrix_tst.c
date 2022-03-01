#include "../WAmatrix.h"
#include "../NGLmatrix.h"
#include "../Umatrix.h"
#include <stdio.h>

void print_mat(Matrix *a)
{
    int i, j;
    for (i = 0; i < a->m; i++)
    {
        for (j = 0; j < a->n; j++)
            printf("%.3f ", a->vals[i][j]);
        printf("\n");
    }
}

int main()
{
    int i;
    Matrix *m = alloc_matrix(10, 2), *WA, *DD, *NGL, *U;

    double nums[10][2] = {{-5.056, 11.011},
                          {-6.409, -7.962},
                          {5.694, 9.606},
                          {6.606, 9.396},
                          {-6.772, -5.727},
                          {-4.498, 8.399},
                          {-4.985, 9.076},
                          {4.424, 8.819},
                          {-7.595, -7.211},
                          {-4.198, 8.371}};
    for (i = 0; i < 10; i++)
    {
        m->vals[i][0] = nums[i][0];
        m->vals[i][1] = nums[i][1];
    }

    WA = create_WA_matrix(m);

    DD = create_DD_matrix(WA);

    NGL = create_NGL_matrix(WA, DD);

    U = create_k_eigenvectors_matrix(NGL, 0, 1);

    free_matrix(m);
    free_matrix(WA);
    free_matrix(DD);
    free_matrix(NGL);
    free_matrix(U);
}