all: player1 player2 
player1: player1.o 
	gcc player1.o -o player1
player2: player2.o
	gcc player2.o -o player2
player1.o: player1.c
	gcc -c player1.c 
player2.o: player2.c
	gcc -c player2.c 
.PHONY: clean
clean:
	rm  *.o player1 player2
