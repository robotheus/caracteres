all: tp3_p2

file.o: file.h file.c
	gcc -c file.c

main.o: main.c
	gcc -c main.c

bmh.o: bmh.h bmh.c
	gcc -c bmh.c

compressao.o: compressao.h compressao.c
	gcc -c compressao.c -lm

tp3_p2: main.o file.o bmh.o compressao.o
	gcc main.o file.o bmh.o compressao.o -o tp3_p2 -lm

clean:
	rm -rf main.o file.o bmh.o compressao.o saida.txt tp3_p2
