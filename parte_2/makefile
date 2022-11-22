all: tp3_p2

file.o: file.h file.c
	gcc -c file.c

main.o: main.c
	gcc -c main.c

bmh.o: bmh.h bmh.c
	gcc -c bmh.c

bmh_compressao.o: bmh_compressao.h bmh_compressao.c
	gcc -c bmh_compressao.c

tp3_p2: main.o file.o bmh.o bmh_compressao.o
	gcc main.o file.o bmh.o -o tp3_p2

clean:
	rm -rf main.o file.o bmh.o bmh_compressao.o saida.txt tp3_p2
