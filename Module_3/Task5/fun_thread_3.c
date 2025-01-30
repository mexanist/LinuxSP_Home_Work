/* Поток приостанавливает свою работу на функции siqwait(),
 как только поток получает сигнал SIGQUIT поток возобнавляет свою работу */

#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <signal.h>


void *fun_thread_3(){
	sigset_t set;
	int sig;
	sigemptyset(&set);
	sigaddset(&set, SIGQUIT);
	pthread_sigmask(SIG_BLOCK, &set, NULL);
	printf("Thread 3 wait for SIGQUIT ...\n");
	sigwait(&set, &sig);
	printf("Thread 3 receive %d, accomplish thread 3\n", sig);// SIGQUIT (3)
}
