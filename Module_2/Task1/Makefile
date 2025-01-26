obj = test.o degree.o 
task_1: $(obj) 
	gcc $(obj) -o task_1
test.o: test.c
	gcc -c test.c 
degree.o: degree.c
	gcc -c degree.c 
.PHONY: clean
clean:
	rm  *.o task_1 
