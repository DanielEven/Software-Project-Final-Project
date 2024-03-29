#include "kmeans.h"

/* kmeans ERROR with memory freeing. */
#define ERROR(msg)            \
    printf("%s\n", msg);      \
    free(num_mapped_vectors); \
    exit(1);

/* Global variables of the arguments and data shape. */
long int k, n, d;
/* Global variable to remember the amount of vectors assigned to each centroid. */
int *num_mapped_vectors = NULL;

double **kmeans(double **vect_arr, double **cents, long int n_local, long int k_local, long int d_local, long int max_iter, double eps)
{
    int i;
    double **new_cents = NULL, ***mapping = NULL;
    const double eps_sqrd = eps * eps;

    /* Assigning the global variables.*/
    n = n_local;
    k = k_local;
    d = d_local;

    if (k >= n || k <= 0)
    {
        free_vect_arr(vect_arr, n);
        ERROR("Invalid Input!");
    }

    if ((num_mapped_vectors = calloc(sizeof(int), k)) == NULL)
    {
        free_vect_arr(vect_arr, n);
        ERROR("An Error Has Occurred");
    }

    for (i = 0; i < max_iter; i++)
    {
        free_arr_of_vect_arr(mapping, k);
        mapping = assign_vetors(vect_arr, cents);

        new_cents = calculate_new_cents(mapping, /*To free*/ vect_arr, /*To free*/ cents);

        if (check_diff_cents_square(cents, new_cents, eps_sqrd))
        {
            free_arr_of_vect_arr(mapping, k);
            free_vect_arr(vect_arr, n);
            free_vect_arr(cents, k);

            free(num_mapped_vectors);
            return new_cents;
        }

        free_vect_arr(cents, k);
        cents = new_cents;
    }

    free_arr_of_vect_arr(mapping, k);
    free_vect_arr(vect_arr, n);

    free(num_mapped_vectors);
    return cents;
}

/* Returns an array of pointers to arrays of pointers to vectors.
The last element of each inner list will be marked by a NULL. */
double ***assign_vetors(double **vect_arr, double **cents)
{
    int i, closest_cent;
    double ***mapping;

    if ((mapping = calloc(sizeof(double **), k)) == NULL)
    {
        free_vect_arr(vect_arr, n);
        free_vect_arr(cents, k);
        ERROR("An Error Has Occurred");
    }

    for (i = 0; i < k; i++)
    {
        mapping[i] = NULL;
        num_mapped_vectors[i] = 0;
    }

    for (i = 0; i < n; i++)
    {
        closest_cent = find_closest(vect_arr[i], cents);

        /* We are allocating also enough memory for the NULL in the end, and for the new vector we are adding.*/
        if ((mapping[closest_cent] = realloc(mapping[closest_cent], (num_mapped_vectors[closest_cent] + 1) * sizeof(double *))) == NULL)
        {
            free_arr_of_vect_arr(mapping, k);
            free_vect_arr(vect_arr, n);
            free_vect_arr(cents, k);
            ERROR("An Error Has Occurred");
        }
        mapping[closest_cent][num_mapped_vectors[closest_cent]++] = vect_arr[i];
    }

    return mapping;
}

/* Returns the index of the centroid closest to vector.*/
int find_closest(double *vect, double **cents)
{
    double min_dist_sqr = DBL_MAX, dist;
    int indx = -1, i;
    for (i = 0; i < k; i++)
    {
        if ((dist = get_dist_sqr(vect, cents[i])) < min_dist_sqr)
        {
            min_dist_sqr = dist;
            indx = i;
        }
    }
    return indx;
}

double get_dist_sqr(double *v1, double *v2)
{
    double sum = 0;
    int i = 0;
    for (i = 0; i < d; i++)
    {
        sum += (v1[i] - v2[i]) * (v1[i] - v2[i]);
    }

    return sum;
}

double **calculate_new_cents(double ***mapping, /*In order to free if there is a problem*/ double **vect_arr, double **old_cents)
{
    double **new_cents, **assigned, *res;
    int i;

    if ((new_cents = calloc(sizeof(double *), k)) == NULL)
    {
        free_arr_of_vect_arr(mapping, k);
        free_vect_arr(vect_arr, n);
        free_vect_arr(old_cents, k);
        ERROR("An Error Has Occurred");
    }

    for (i = 0; i < k; i++)
    {
        if ((res = calloc(sizeof(double), d)) == NULL)
        {
            free_arr_of_vect_arr(mapping, k);
            free_vect_arr(vect_arr, n);
            free_vect_arr(old_cents, k);
            free_vect_arr(new_cents, k);
            ERROR("An Error Has Occurred");
        }
        assigned = mapping[i];
        vector_sum(res, assigned, num_mapped_vectors[i]);
        devide_vector(res, num_mapped_vectors[i]);
        new_cents[i] = res;
    }

    return new_cents;
}

/* The result should be returned through the sum parameter.*/
void vector_sum(double *sum, double **vectors, int len_lst)
{
    int i, j;

    for (i = 0; i < d; i++)
    {
        for (j = 0; j < len_lst; j++)
        {
            sum[i] += vectors[j][i];
        }
    }
}
void devide_vector(double *vect, double alpha)
{
    int i;

    for (i = 0; i < d; i++)
    {
        vect[i] = vect[i] / alpha;
    }
}

/* Returns 1 (True) if all of the centroids haven't moved more then epsilon, else 0 (False). */
int check_diff_cents_square(double **cents, double **new_cents, double eps_sqrd)
{
    int i;
    for (i = 0; i < k; i++)
    {
        if (!(get_dist_sqr(cents[i], new_cents[i]) <= eps_sqrd))
        {
            return 0;
        }
    }
    return 1;
}