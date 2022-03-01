# Python interface of the code.
import sys
import numpy as np
import pandas as pd
from spkmeansmodule import process_data_for_spectral_clustering, kmeans


def get_arguments():
    argc = len(sys.argv)

    try:
        if argc != 4:  # max_iter is not provided.
            raise ValueError()

        k = int(sys.argv[1])
        goal = sys.argv[2]
        file_name = sys.argv[3]
        # Checking enum
        assert(goal in ["spk", "wam", "ddg", "lnorm", "jacobi"])
        # Checking the file type.
        assert(file_name.endswith(".txt") or file_name.endswith(".csv"))

        return k, goal, file_name
    except (ValueError,  AssertionError):
        print("Invalid Input!")
        sys.exit(1)


def read_data(file_name):

    # Reading the data.
    df = pd.read_csv(file_name, header=None)

    return df


def kmeans_pp(data, k):
    np.random.seed(0)

    N = data.shape[0]

    # Initializing the data.
    first_index = np.random.choice(N)
    cents = [data[first_index, :]]
    cents_indexes = [first_index]

    i = 1
    while i < k:

        # Calculating the minimal distance for each vector.
        D_list = [min([np.dot(data[l, :] - cents[j], data[l, :] - cents[j])
                      for j in range(i)]) for l in range(N)]

        # Calculating the probabilities for selection.
        d_sum = sum(D_list)
        P_list = [(D_list[l]/d_sum) for l in range(N)]

        i += 1

        # Choosing the index using the probabilities.
        chosen_index = np.random.choice(np.arange(N), p=np.array(P_list))

        # Adding the index & vector to the corresponding lists.
        cents_indexes.append(chosen_index)
        cents.append(data[chosen_index, :])

    return pd.DataFrame(cents), cents_indexes


def print_output(result, chosen_indexes):
    # Print the chosen indexes.
    if chosen_indexes is not None:
        print_initials(chosen_indexes)

    # Print each row.
    for index, centroid in result.iterrows():
        print_centroid(centroid)


def print_initials(initials):
    for index, ind in enumerate(initials):

        # Print the initial observation index.
        print(ind, end="")

        # Print , or new line.
        if index != (len(initials) - 1):
            print(',', end="")
        else:
            print()


def print_centroid(centroid):
    for index, coor in enumerate(centroid):

        # Print the coordinate.
        print("%.4f" % coor, end="")

        # Print, or newline.
        if index != (len(centroid) - 1):
            print(',', end="")
        else:
            print()


def main():
    # Getting and cheking all arguments (except checking 0 < k < n).
    k, goal, file_name = get_arguments()

    try:

        # Reading the data.
        data = read_data(file_name)

        # Checking that 0 < k < n.
        if (k < 0) or (k >= data.shape[0]):
            print("Invalid Input!")
            sys.exit(1)

        # Use the Normalized Spectral Clustering Algorithm in order to make the data ready for kmeans.
        processed_data = process_data_for_spectral_clustering(
            data.values.tolist(), k, goal)

        if goal == "spk":
            # Calculating initial centroids
            init_cents, chosen_indexes = kmeans_pp(
                np.array(processed_data), len(processed_data[0]))

            # Calculate the centroids.
            result = kmeans(processed_data,
                            init_cents.values.tolist())

            # Moving the returned data back to a DataFrame.
            result_df = pd.DataFrame(result)

        else:
            result_df = pd.DataFrame(processed_data)
            chosen_indexes = None

        # Writing the calculated centroids.
        print_output(result_df, chosen_indexes)

    except:
        print("An Error Has Occurred!")
        sys.exit(1)


if __name__ == '__main__':
    main()
