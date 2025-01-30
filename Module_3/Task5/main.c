/* Программа создает три потока, первый поток блокирует все сигналы, второй поток
 через обработчик принимает сигнал SIGINT и завершает свою работу, третий поток 
 с помощью функции sigwait() дожидается сигнала SUGQUIT и завершает свою работу.
 После завершения 2 и 3 потоков, происходит отмена потока 1, таким образом программа заканчивает
 свою работу */

#include "main.h"

int main(){
	pthread_t t_1, t_2, t_3;
	int s_1, s_2, s_3;
	printf("Test threads:\n");
	s_1 = pthread_create(&t_1, NULL, fun_thread_1, NULL);
	s_2 = pthread_create(&t_2, NULL, fun_thread_2, NULL);
	s_3 = pthread_create(&t_3, NULL, fun_thread_3, NULL);
	if ((s_1 != 0) || (s_2 != 0) || (s_3 != 0)){
		perror("create thread failure");
		exit(EXIT_FAILURE);
	}
/* Для проверки блокировки сигналов в поток 1 пять раз посылается
 сигналы SIGINT и SIGQUIT */
	for (int i = 0; i < 5; i++){
		sleep(1);
		pthread_kill(t_1, SIGINT);
		pthread_kill(t_1, SIGQUIT);
	}
	sleep(1);
	pthread_kill(t_2, SIGINT);
	sleep(2);
	pthread_join(t_2, NULL);
	pthread_kill(t_3, SIGQUIT);
	sleep(2);
	pthread_join(t_3, NULL);
	pthread_cancel(t_1);
	printf("All threads finished\n");
}
