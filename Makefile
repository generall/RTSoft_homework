matrix: libmatrix.so main.o
	gcc main.o -L. -lmatrix -pthread -o matrix
main.o: main.c libmatrix.h
	gcc -std=c99 -c main.c
libmatrix.so: libmatrix.o
	gcc -shared -o libmatrix.so libmatrix.o
libmatrix.o: libmatrix.h libmatrix.c
	gcc -fPIC -std=c99 -pthread -c libmatrix.c