#include "../matrix.h"
#include <stdio.h>

void print_mat(Matrix *a)
{
    int i, j;
    for (i = 0; i < a->m; i++)
    {
        for (j = 0; j < a->n; j++)
            printf("%f ", a->vals[i][j]);
        printf("\n");
    }
}

int main()
{
    Matrix *m1 = alloc_matrix(2, 2);
    m1->vals[0][0] = 1;
    m1->vals[0][1] = 2;
    m1->vals[1][0] = 3;
    m1->vals[1][1] = 4;
    Matrix *m2 = alloc_matrix(2, 2);
    m2->vals[0][0] = 1;
    m2->vals[0][1] = 1;
    m2->vals[1][0] = 1;
    m2->vals[1][1] = 1;
    Matrix *res;

    print_mat(m1);
    printf("+\n");
    print_mat(m2);
    printf("=\n");
    res = add_matrix(m1, m2);
    print_mat(res);

    free_matrix(m1);
    free_matrix(m2);
    free_matrix(res);
    return 0;
}