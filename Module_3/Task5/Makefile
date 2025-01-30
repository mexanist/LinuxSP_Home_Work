obj = main.o fun_thread_1.o fun_thread_2.o fun_thread_3.o
task_5: $(obj)
	gcc $(obj) -o task_5 -lpthread
main.o: main.c
	gcc -c main.c -lpthread
fun_thread_1.o: fun_thread_1.c
	gcc -c fun_thread_1.c
fun_thread_2.o: fun_thread_2.c
	gcc -c fun_thread_2.c -lpthread
fun_thread_3.o: fun_thread_3.c
	gcc -c fun_thread_3.c -lpthread
.PHINY: clean
clean:
	rm -rf *.o task_5
