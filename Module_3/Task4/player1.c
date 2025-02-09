/* Программа шахматных ходов. Поочередно считывает ходы Player1 и Player2 в общую очередь,
 затем читает и выводит на экран сообщения из этой очереди. Очередность ходов реализуется 
 с помощью двух семафоров System5 взаимным исключением 
 Семафор 0 - Player1
 Семафор 1 - Player2 
*/
#include "player.h"

int main(){
	char *turns[] = {"W_e4", "W_Nf3", "W_Bd5", "W_Ba4", "W_O-O", "W_d3", "W_Bb3", "W_a4", "W_h3", 
					 "W_Be3", "W_Ba2", "W_Nc3", "W_Bd1", "W_b3", "W_Nxa4", "W_Nc3", "W_Nd2", "W_Nc4",
					 "W_exd5", "W_Bd2", "W_Bxc3", "W_Bxc3", "W_Bxc3", "W_c3", "W_Re1", "W_Ra2", "W_Qe2",
					 "W_g3", "W_Qf3", "W_dxe4", "W_Qg2", "W_Bxd3", "W_exf5", "W_Bxe1", "W_Ra1", "W_Bd2",
					 "W_Qc6", "W_Re1", "W_Be3", "W_Qe8", "W_Rc1", "W_Qd7", "W_Qd5", "W_Qe4+", "W_Qd5+", "W_Qd4+",
					 "W_Qf5", "W_h4", "W_Qf3", "W_Qg4", "W_Rd1", "W_Qc8", "W_Qa8", "W_Rxd6", "W_Qe4+", "W_Qc4",
					 "W_Kh2", "W_Bd4", "W_Qc7", "W_Qc4", "W_Be3", "W_Kg2", "W_Kf1", "W_g4", "W_h5", "W_Qd5", 
					 "W_f4", "W_Qxa2", "END"};//Ходы белых (Player1)
	key_t id_que, id_sem;
	int msgid, semid, len_msg, len_trn;
	len_trn = sizeof(turns)/sizeof(turns[0]);
	struct msgbuf msg;
/* semaphore */
	if((id_sem = ftok("player1.c", 't')) == -1){
		perror("fail id_sem");
		exit(1);
	}
	if((semid = semget(id_sem, 2, 0666 | IPC_CREAT)) == -1){
        perror("semget fail");
        exit(EXIT_FAILURE);
    }
/* Установка семафора для Player1 */
    if (semctl(semid, 0, SETVAL, 1) == -1) {
        perror("semctl SETVAL");
        exit(EXIT_FAILURE);
    }
/* Установка семафора для Player2 */
     if (semctl(semid, 1, SETVAL, 0) == -1) {
         perror("semctl SETVAL");
         exit(EXIT_FAILURE);
     }
/*queue */
	if((id_que = ftok("player2.c", 'r')) == -1){
		perror("fail id_que");
		exit(1);
	}
	if((msgid = msgget(id_que, 0666 | IPC_CREAT)) == -1){
		perror("fail create queue");
		exit(1);
	}
	struct sembuf ops[2];
	ops[0].sem_num = 0;
	ops[1].sem_num = 1;
	ops[0].sem_flg = SEM_UNDO;
	ops[1].sem_flg = SEM_UNDO;
/* Отправка сообщений в очередь Player1*/
	for(int i = 0; i < len_trn; i++){
/* Захватываем семафор 0 */
		ops[0].sem_op = -1;
		if(semop(semid, ops, 1) == -1) {
                perror("semop lock");
                exit(EXIT_FAILURE);
        }
		msg.type = 1;
		strcpy(msg.text, turns[i]);
		if ((msgsnd(msgid, &msg, strlen(msg.text) + 1, 0)) == -1){
			perror("fail send message");
			msgctl(msgid, IPC_RMID,  NULL);
			exit(1);
		}
/* Освобождаем семафор 1 */
			ops[1].sem_op = 1;	
            if(semop(semid, ops + 1, 1) == -1) {
                perror("semop unlock (child)");
                exit(EXIT_FAILURE);
            }
	}
/* Читаем очередь, партия Дин Лижэнь - Я.Непомнящий */
	while(1){
        if((len_msg = msgrcv(msgid, &msg, sizeof(msg.text), 0, 0)) < 0){
            perror("fail read from queue");
            exit(1);
        }
         if(!strcmp(msg.text, "END")){
            printf("END\n");
            if((msgctl(msgid, IPC_RMID,  NULL)) == -1){
                perror("fail delete queue");
            }
			semctl(semid, 1, IPC_RMID);
            exit(0);
        }
    printf("Turn %s\n", msg.text);
    }
}
