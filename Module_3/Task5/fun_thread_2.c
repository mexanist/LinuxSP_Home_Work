/* Поток принимает сигнал SIGINT и обрабатывает с помощью обработчика sig_handler()
  Для завершения бесконечного цикла и завершения работы потока используется глобальный флаг 
  stop_thread_2 */

#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <signal.h>

/* volatile гарантирует что над этой переменной не будет произведена какая либо оптимизация
 sig_atomic_t - целочисленный тип чтение и запись которого являются атомарными операциями 
 Керриск гл21, стр.454 */

volatile sig_atomic_t stop_thread_2 = 0;// глобальная переменная флага

void sig_handler(int sig){
	printf("Thread 2 reseive signal SIGINT\n");
	stop_thread_2 = 1;
}
void *fun_thread_2(){
	struct sigaction test;
	sigemptyset(&test.sa_mask);
	test.sa_flags = 0;
	test.sa_handler = sig_handler;
	sigaction(SIGINT, &test, NULL);
	while(!stop_thread_2){
		printf("Thread 2 working...\n");
		sleep(1);
	}
	printf("Accomplich thread 2\n");
}
