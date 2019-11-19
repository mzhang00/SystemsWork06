all: work06.o
	gcc -o program work06.o

work06.o: work06.c
	gcc -c work06.c

run:
	./program
