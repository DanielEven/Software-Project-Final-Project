# The compilation script.
gcc kmeans.c matrix.c NGLmatrix.c spkmeans.c Tmatrix.c Umatrix.c vector.c WAmatrix.c \
     -lm -g -o spkmeans