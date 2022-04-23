#! /bin/bash

# The compilation script.
gcc -ansi -Wall -Wextra -Werror -pedantic-errors kmeans.c matrix.c NGLmatrix.c spkmeans.c Tmatrix.c Umatrix.c vector.c WAmatrix.c \
     -lm -o spkmeans