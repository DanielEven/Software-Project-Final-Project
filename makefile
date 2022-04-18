
# Building the c code not from the python setup.py file.
output:
	/bin/sh comp.sh

# Building the c code as a library, using the setup.py file.
python:
	python3 setup.py build_ext --inplace

# Running the python code, using the library we have built.
python_run:
	python3 spkmeans.py 0 spk tests/blobs1.txt

# Deleting the output files.
clean:
	rm -f out spkmeans
	rm -f tests/testers/*.txt
	rm -f *.so
	rm -rf build/

## Testing different c files:

# Matrix
test_matrix: tests/matrix_tst.c
	gcc kmeans.c matrix.c NGLmatrix.c Tmatrix.c Umatrix.c vector.c WAmatrix.c tests/matrix_tst.c \
     -lm -g -o out
# Weighted Adjacency Matrix
test_wa_matrix: tests/WA_matrix_tst.c
	gcc kmeans.c matrix.c NGLmatrix.c Tmatrix.c Umatrix.c vector.c WAmatrix.c tests/WA_matrix_tst.c \
     -lm -g -o out
# Normalized Graph Laplacian Matrix
test_ngl_matrix: tests/NGL_matrix_tst.c
	gcc kmeans.c matrix.c NGLmatrix.c Tmatrix.c Umatrix.c vector.c WAmatrix.c tests/NGL_matrix_tst.c \
     -lm -g -o out
