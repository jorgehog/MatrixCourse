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

To get access to the code in netbeans, perform the following steps:

1: Create a new c++ application project (located outside the git repository)
2: Right click the project and select "add excisting items from folder" and select the "/code" folder.
3: Include matrixHeaders.h in your main file. E.g.  #include "../../MASTER/MatrixCourse/code/matrixHeaders.h"
