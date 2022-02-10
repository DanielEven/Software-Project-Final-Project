
# Building the c code not from the python setup.py file.
output:
	gcc -I/usr/include/python3.8 *.c -lm -g -o out -L/usr/lib/x86_64-linux-gnu/libpython3.8.so -lpython3.8

# Building the c code as a library, using the setup.py file.
python:
	python3 setup.py build_ext --inplace

# Deleting the output files.
clean:
	rm out

## Testing different c files:

# Matrix
test_matrix: matrix.c tests/matrix_tst.c
	gcc -I/usr/include/python3.8 matrix.c tests/matrix_tst.c -lm -g -o out -L/usr/lib/x86_64-linux-gnu/libpython3.8.so -lpython3.8