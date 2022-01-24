
# building
output: kmeans.c
	python3 setup.py build_ext --inplace

#Checking Python
python: kmeans_pp.py
	gcc tests/tester.c -o tst
	./tst
	rm tst
	python3 tests/tester.py
	cd ..

# Cleaning
clean:
	rm -f tests/*.txt
	rm *.so
