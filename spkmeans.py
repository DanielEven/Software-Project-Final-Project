# Python interface of the code.
import sys


def get_arguments():
    argc = len(sys.argv)

    try:
        if argc != 4:  # max_iter is not provided.
            raise ValueError()

        k = int(sys.argv[1])
        goal = sys.argv[2]
        file_name = sys.argv[3]
        assert(goal in ["spk", "wam", "ddg", "lnorm", "jacobi"]) # Checking enum
        assert(file_name.endswith(".txt") or file_name.endswith(".csv"))  # Checking the file type.

        return k, goal, file_name
    except (ValueError,  AssertionError):
        print("Invalid Input!")
        sys.exit(1)

