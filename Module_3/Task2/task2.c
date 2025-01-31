/* Программа выводит свой pid процесса, затем ждет одну секунду и делает
 exec самой себя */

#include <stdio.h>
#include <unistd.h>
#include <string.h>

static int count = 0;
const int max_run = 5;

int main(int argc, char *argv[]){
	printf("Pid is %d\n", getpid());
	sleep(1);
	printf("%s \n", argv[1]);
/* При первом вызове execl ей в качестве аргументов передаетутся аргументы
 переданные при первом запуске программы и аргумент "1", который будет первым аргументом
 при следующем вызове execl. Затем этот аргумент используется при повторном вызове execl 
 который предотвращает бесконечное выполнение программы */
	if (strcmp(argv[0], "1") != 0){
		execl("task2", "1", argv[1], NULL);
	}
	if (strcmp(argv[0], "1") == 0){
		printf("%s\n", argv[1]);
	}

}
