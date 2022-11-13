all: tp3

file.o: file.h file.c
	gcc -c file.c

main.o: main.c
	gcc -c main.c

shiftand.o: shiftand.h shiftand.c
	gcc -c shiftand.c

tp3: main.o file.o shiftand.o
	gcc main.o file.o shiftand.o -o tp3

clean:
	rm -rf main.o file.o shiftand.o saida.txt tp3