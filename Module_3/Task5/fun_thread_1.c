/* Поток блокирует все сигналы, за исключением SIGKILL и SIGSTOP. 
 В сигнальную маску добавляются все сигналы с помощбю sigfillset().
 Поток работает до тех пор, пока его не отменит породившая программа */

#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <signal.h>

void *fun_thread_1(){
	sigset_t set;
	sigfillset(&set);
/* По аналогии с sigmask(), SIGKILL и SIGSTOP нельзя заблокировать, иначе 
   при получении одного из этих сигналов произойдет ошибка  */
	if (pthread_sigmask(SIG_BLOCK, &set, NULL) != 0){
		perror("block signal failure");
		exit(EXIT_FAILURE);
	}
	while (1){
		printf("Thread 1 working blocks signals...\n");
		sleep(1);
	}
}
