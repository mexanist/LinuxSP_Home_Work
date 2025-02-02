#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <time.h>
#define N 30
int main(){
    int *array;   /* Указатель на разделяемую память */
    int shmid;    /* IPC дескриптор для области разделяемой памяти */
    int new = 1;  /* Флаг необходимости инициализации элементов массива */
    char pathname[] = "player1.c"; /* Имя файла, 
        используемое для генерации ключа. Файл с таким 
        именем должен существовать в текущей директории */
    key_t key;    /* IPC ключ */ 
    /* Генерируем IPC ключ из имени файла 06-1a.c в 
    текущей директории и номера экземпляра области 
    разделяемой памяти 0 */
    if((key = ftok(pathname,0)) < 0){
        printf("Can\'t generate key\n");
        exit(-1);
    }
    /* Пытаемся эксклюзивно создать разделяемую память
    для сгенерированного ключа, т.е. если для этого 
    ключа она уже существует, системный вызов вернет
    отрицательное значение. Размер памяти определяем 
    как размер массива из трех целых переменных, права 
    доступа 0666 – чтение и запись разрешены для всех */
    if((shmid = shmget(key, 7*sizeof(int), 
        0666|IPC_CREAT|IPC_EXCL)) < 0){
    /* В случае возникновения ошибки пытаемся определить: 
    возникла ли она из-за того, что сегмент разделяемой 
    памяти уже существует или по другой причине */
        if(errno != EEXIST){
            /* Если по другой причине – прекращаем работу */
            printf("Can\'t create shared memory\n");
            exit(-1);
        } else {
            /* Если из-за того, что разделяемая память уже
            существует, то пытаемся получить ее IPC дескриптор
            и, в случае удачи, сбрасываем флаг необходимости
            инициализации элементов массива */
            if((shmid = shmget(key, 5*sizeof(int), 0)) < 0){
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
    if((array = (int *)shmat(shmid, NULL, 0)) == 
        (int *)(-1)){
        printf("Can't attach shared memory\n");
        exit(-1);
    }
    /* В зависимости от значения флага new либо 
    инициализируем массив, либо увеличиваем 
    соответствующие счетчики */ 
    if(new){
        array[0] = 0;
        array[1] = 1;
        array[2] = 0;
		array[3] = 0;
		array[4] = 0;
		array[5] = (int)time(NULL);
		array[6] = 1;
    } else {
		if (!array[4] && array[6]){
        	int cur_time = (int)time(NULL);
			array[1] = cur_time - array[5];
			array[5] = (int)time(NULL);
			array[3] = array[3] + array[1];
        	if (array[3] > N){
            	printf("Player2 lost game.\n");
            	shmdt(array);
            	exit(0);
        	}
			array[4] = 1;
    	} else {
			printf("Turn of player1\n");
            shmdt(array);
            exit(0);
		}
	} 
    /* Печатаем новые значения счетчиков, удаляем разделяемую
    память из адресного пространства текущего процесса и 
    завершаем работу */
    printf("PLAYER2: finished %d seconds, total time %d second\n", array[1], array[3]);
    if(shmdt(array) < 0){ 
        printf("Can't detach shared memory\n");
        exit(-1);
    }
    return 0;
}
