all: tp3

file.o: file.h file.c
	gcc -c file.c

main.o: main.c
	gcc -c main.c

tp3: main.o file.o
	gcc main.o file.o -o tp3

clean:
	rm -rf main.o file.o saida.txt tp3