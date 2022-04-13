#ifndef SPKMEANS_H
#define SPKMEANS_H

/* C Interface of the code.*/
/* Has a function to manage the calls to all of the C files. */

#include "spkmeans.h"

int main(int argc, char *argv[])
{
    double **centroids;
    char *goal;
    FILE *input_file;
    Matrix *input_mat, *result;
    if (argc != 3)
    {
        ERROR("Invalid Input!");
    }

    goal = argv[1];
    if (strcmp(goal, "wam") && strcmp(goal, "ddg") && strcmp(goal, "lnorm") && strcmp(goal, "jacobi"))
    {
        ERROR("Invalid Input!");
    }

    input_file = fopen(argv[2], "r");
    if (input_file == NULL)
    {
        ERROR("Invalid Input!");
    }

    input_mat = read_input(input_file);

    fclose(input_file);

    if (input_mat == NULL)
    {
        ERROR("Invalid Input!");
    }

    result = calculate_requested(input_mat, 0, goal);
    free_matrix(input_mat);
    if (result == NULL)
    {
        ERROR("Invalid Input!");
    }

    free_matrix(result);
    write_output(result);
    return 0;
}

/* The function also counts the vector amount - n, and the vector's dimension - d.*/
Matrix *read_input(FILE *input_file)
{
    Matrix *to;
    double num;
    int i, j, n, d;

    n = get_n(input_file);
    d = get_d(input_file);

    to = alloc_matrix(n, d);
    if (to == NULL)
    {
        return NULL;
    }

    for (i = 0; i < n; i++)
    {
        for (j = 0; j < d; j++)
        {
            fscanf(input_file, "%lf,", &num);
            to->vals[i][j] = num;
        }
    }

    return to;
}

int get_n(FILE *input_file)
{
    char ch;
    int n = 0;
    while ((ch = fgetc(input_file)) != EOF)
    {
        if (ch == '\n')
            n++;
    }
    rewind(input_file);
    return n;
}

int get_d(FILE *input_file)
{
    char ch;
    int d = 1;
    while ((ch = fgetc(input_file)) != '\n')
    {
        if (ch == ',')
            d++;
    }
    rewind(input_file);
    return d;
}

void write_output(Matrix *result)
{
    // LIAM
}

Matrix *calculate_requested(Matrix *data_matrix, long int k, const char *goal)
{
    Matrix *WA, *DD, *NGL, *U, *T;

    WA = create_WA_matrix(data_matrix);
    if (!strcmp(goal, "wam") || (WA == NULL))
    {
        return WA;
    }

    DD = create_DD_matrix(WA);
    if (!strcmp(goal, "ddg") || (DD == NULL))
    {
        free_matrix(WA);
        /* TODO pow_diag_matrix_inp(DD, -0.5); - this outputs DD^-1/2 like in the project_clarification.docx file*/
        return DD;
    }

    NGL = create_NGL_matrix(WA, DD);
    free_matrix(WA);
    free_matrix(DD);

    if (!strcmp(goal, "lnorm") || (NGL == NULL))
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
        if (U == NULL)
            return U;
        T = get_row_normalized_matrix(U);
        free_matrix(U);
        return T;
    }

    return NULL;
}

#endif