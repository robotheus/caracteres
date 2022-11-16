all: tp3_p1

file.o: file.h file.c
	gcc -c file.c

main.o: main.c
	gcc -c main.c

shiftand.o: shiftand.h shiftand.c
	gcc -c shiftand.c

dinamica.o: dinamica.h dinamica.c
	gcc -c dinamica.c

tp3_p1: main.o file.o shiftand.o dinamica.o
	gcc main.o file.o shiftand.o dinamica.o -o tp3_p1

clean:
	rm -rf main.o file.o shiftand.o dinamica.o saida.txt tp3_p1
