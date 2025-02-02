/* Программа эмулирует шахматные часы с помощью разделяемой памяти, с следующими условиями:
 1. Каждая программа сохраняет время запуска другой программы (переменная  array[5])
 2. Игроки ходят по очереди
 3. Если суммарное время одного из программ-игроков превышает заданный порог (переменная N) 
 обе показывают сообщение "Техническое поражение чёрных/белых"  

 Player1 - белые
 Player2 - черные
*/
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <time.h>
#define N 30//время отведенное на игру

int main(){
    int *array;    /* Указатель на разделяемую память */
    int shmid;     /* IPC дескриптор для области разделяемой памяти */
    int new = 1;   /* Флаг необходимости инициализации элементов массива */
    char pathname[] = "player1.c";
    key_t key;     /* IPC ключ */
    if((key = ftok(pathname,0)) < 0){
        printf("Can\'t generate key\n");
        exit(-1);
    }
    if((shmid = shmget(key, 7*sizeof(int), 0666|IPC_CREAT|IPC_EXCL)) < 0){
    /* В случае ошибки пытаемся определить: возникла ли она
    из-за того, что сегмент разделяемой памяти уже существует
    или по другой причине */
        if(errno != EEXIST){
            /* Если по другой причине – прекращаем работу */
            printf("Can\'t create shared memory\n");
            exit(-1);
        } else {
            if((shmid = shmget(key, 3*sizeof(int), 0)) < 0){
                printf("Can\'t find shared memory\n");
                exit(-1);
            }
            new = 0;
        }
    }
    /* Пытаемся отобразить разделяемую память в адресное 
    пространство текущего процесса. Обратите внимание на то,
    что для правильного сравнения мы явно преобразовываем 
    значение -1 к указателю на целое.*/ 

    if((array = (int *)shmat(shmid, NULL, 0)) == (int *)(-1)){
        printf("Can't attach shared memory\n");
        exit(-1);
    }
    /* Старт игры */ 
    if(new){
        array[0] = 1;//время хода Player1
        array[1] = 0;//время хода Player2
        array[2] = 0; //суммарное количество времени Player1
		array[3] = 0; // суммарное количество времени Player2
		array[4] = 0;//очередность хода Player1 белые фигуры 
		array[5] = (int)time(NULL);//время конца хода, инициализируется отдельно каждым игроком по очереди
		array[6] = 1;//Флаг выигрыша/поражения
/* Ход игры */
    } else {
		if (array[4] && array[6]){
			int cur_time = (int)(time(NULL));
        	array[0] = cur_time - array[5];
			array[5] = (int)time(NULL);
			array[2] = array[2] + array[0];
/* Условие проигрыша */
			if (array[2] > N){
				printf("Player1 lost game.\n");
				array[6] = 0;
				shmdt(array);
				exit(0);
			}
			array[4] = 0;
    	} else {
			printf("Nope. Turn of player2\n");
			shmdt(array);
			exit(0);
		}
	}
    /* Печатаем новые значения счетчиков, удаляем 
    разделяемую память из адресного пространства 
    текущего процесса и завершаем работу */
    printf("PLAYER1: finished %d seconds, total time %d second \n", array[0], array[2]);
    if(shmdt(array) < 0){ 
        printf("Can't detach shared memory\n");
        exit(-1);
    }
    return 0;
}
