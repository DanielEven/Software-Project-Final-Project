#include "matrix.h"
#include "vector.h"
#include "WAmatrix.h"
#include "NGLmatrix.h"
#include "Umatrix.h"
#include "Tmatrix.h"

#include <string.h>
#include <stdio.h>

#define ERROR(msg)       \
    printf("%s\n", msg); \
    exit(1);

/* Function for input reading from C running. */
Matrix *read_input(FILE *input_file);
/* Getting the input dimensions from the input file. */
int get_n(FILE *input_file);
int get_d(FILE *input_file);
/* Function for output printing in C running. */
void write_output(Matrix *result);

/* A function to calculate the result, by sending the data_matrix to the right function - according to goal. */
Matrix *calculate_requested(Matrix *data_matrix, long int k, const char *goal);

/* A function to flip the -0.0000 of the values to be 0.0000 in the first row, for the printing. */
void fix_first_row_for_print(double *row, int n);

#define CHECK_SYMETRIC(mat)      \
    if (!is_symetric(mat))       \
    {                            \
        ERROR("Invalid Input!"); \
    }
