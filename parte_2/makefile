all: tp3_p2

file.o: file.h file.c
	gcc -c file.c

main.o: main.c
	gcc -c main.c

bmh1.o: bmh1.h bmh1.c
	gcc -c bmh1.c

compressao.o: compressao.h compressao.c
	gcc -c compressao.c

tp3_p2: main.o file.o bmh1.o compressao.o
	gcc main.o file.o bmh1.o -o tp3_p2

clean:
	rm -rf main.o file.o bmh1.o compressao.o saida.txt tp3_p2
