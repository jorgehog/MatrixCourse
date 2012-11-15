A compilation note from each chapter is saved in respective folders (should be organized by chapters later on).

All code is located in the ./code path with the following guidelines:
	-For each new method or submethod, create a new source folder
	-Add your methods to the matrixHeaders.h header file
	-Use the armadillo library for matrix algebra
	-Send armadillo matrices to function (pointers is more a hazzle)
		e.g. void foo(arma::mat & G);
	-Avoid global namespaces (use std and arma locally inside functions)
	-Comment the headerfile declaration with a short note and the algorithm number in the book.

	See examples "house, givens, hessenberg*" for guidelines.
