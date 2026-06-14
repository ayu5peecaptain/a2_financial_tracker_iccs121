#-*-MakeFile-*- 
.PHONY: main.c main.h 

main: main.o
	gcc main.o -o fintrack 

main.o: main.c main.h
	gcc -c -Wall main.c
clean:
	rm *.o main 
