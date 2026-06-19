#-*-MakeFile-*- 

fintrack: src/main.o
	gcc src/main.o -o release/fintrack 

src/main.o: src/main.c include/main.h
	gcc -c -Wall src/main.c -o src/main.o

dist: include/main.h src/main.c release/fintrack report/report.pdf
	zip -r dist/6781753-ICCS121-A2.zip include/ release/ src/ logs/ report/ Makefile

clean: 
	rm -f src/*.o
	rm -f release/fintrack
