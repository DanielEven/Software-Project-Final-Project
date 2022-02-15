
# Building the c code not from the python setup.py file.
output:
	gcc -I/usr/include/python3.8 *.c -lm -g -o out -L/usr/lib/x86_64-linux-gnu/libpython3.8.so -lpython3.8

# Building the c code as a library, using the setup.py file.
python:
	python3 setup.py build_ext --inplace

# Deleting the output files.
clean:
	rm -f out
	rm -f tests/testers/*.txt

## Testing different c files:

# Matrix
test_matrix: tests/matrix_tst.c
	gcc -I/usr/include/python3.8 *.c tests/matrix_tst.c -lm -g -o out -L/usr/lib/x86_64-linux-gnu/libpython3.8.so -lpython3.8
# Weighted Adjacency Matrix
test_wa_matrix: tests/WA_matrix_tst.c
	gcc -I/usr/include/python3.8 *.c tests/WA_matrix_tst.c -lm -g -o out -L/usr/lib/x86_64-linux-gnu/libpython3.8.so -lpython3.8
# Normalized Graph Laplacian Matrix
test_ngl_matrix: tests/NGL_matrix_tst.c
	gcc -I/usr/include/python3.8 *.c tests/NGL_matrix_tst.c -lm -g -o out -L/usr/lib/x86_64-linux-gnu/libpython3.8.so -lpython3.8
# Eigenvectors and Eigenvalues
test_u_matrix: tests/U_matrix_tst.c
	gcc -I/usr/include/python3.8 *.c tests/U_matrix_tst.c -lm -g -o out -L/usr/lib/x86_64-linux-gnu/libpython3.8.so -lpython3.8 -DTESTING_JACOBI