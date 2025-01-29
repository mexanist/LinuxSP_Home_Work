all: signal fread 
signal: signal.o 
	gcc signal.o -o signal
fread: fread.o
	gcc fread.o -o fread
signal.o: signal.c
	gcc -c signal.c 
fread.o: fread.c
	gcc -c fread.c 
.PHONY: clean
clean:
	rm  *.o signal fread 
