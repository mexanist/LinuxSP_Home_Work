#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <string.h>
#include <fcntl.h>
#include <errno.h>

/* Новый обработчик сигнала */
void sig_handler(int sig){
	int fd;
	char *str = "Resieve signal SIGABRT";
/* Открываем очередь только на запись и пишем туда то что содержится в str */
	fd = open("/tmp/fifo_signal", O_WRONLY);
	if (fd == -1){
		perror("fifo open failure");
		exit(EXIT_FAILURE);
	}
	if(write(fd, str, strlen(str)) == -1){
		perror("write fifo failure");
		exit(EXIT_FAILURE);
	}
	if(close(fd) == -1){
		perror("fifo close failure");
		exit(EXIT_FAILURE);
	}
}
int main(){
	struct sigaction test;
/* Создаем очередь и проверяем на ошибку существования файла,
 * если файл существует то норм */
	if ((mkfifo("/tmp/fifo_signal", S_IRUSR | S_IWUSR | S_IWGRP) == -1) && errno != EEXIST){
		perror("fifo create failure");
		exit(EXIT_FAILURE);
	}
/* Зполнение структуры sigaction, т.к. во время вызова обработчика для сигнала
 этот сигнал автоматически попадает в сигнальную маску, то его можно явно не добавлять туда */
	sigemptyset(&test.sa_mask);
	test.sa_handler = sig_handler;
	test.sa_flags = 0;
/* Смена диспозиции сигнала */
	if (sigaction(SIGABRT, &test, NULL) == -1){
		perror("sigaction fail");
		exit(EXIT_FAILURE);
	}
	puts("Waiting for someone to open the fifo...");
/* Отправляем сами себе сигнал */
	raise(SIGABRT);
}
