/* Второй игрок */
#include "player.h"

int main(){
	char *turns[] = {"B_e5", "B_Nc6", "B_a6", "B_Nf6", "B_Be7", "B_b5", "B_d6", "B_Bd7", "B_O-O",
                     "B_Na5", "B_bxa4", "B_Rb8", "B_Qe8", "B_c5", "B_Nc6", "B_a5", "B_Be6", "B_d5",
                     "B_Nxd5", "B_Nxc3", "B_Bxc4", "B_Bd8", "B_Bc7", "B_f5", "B_Rd8", "B_Qg6", "B_Qd6",
                     "B_Rde8", "B_e4", "B_Ne5", "B_Nd3", "B_Qxd3", "B_Rxe1+", "B_Qxc4", "B_Rxf5", "B_h6", 
                     "B_Rf7", "B_Kh7", "B_Be5", "B_Bxc3", "B_Rf6", "B_Qe2", "B_Bd4", "B_Kg8", "B_Kh7", "B_Rg6", 
                     "B_c4", "B_Qd3", "B_Rf6", "B_c3", "B_Qg6", "B_Rc6", "B_Rd6", "B_Qxd6", "B_Qg6", "B_Qb1+", 
  				     "B_a4", "B_a3", "B_Qg6", "B_c2", "B_Bd6", "B_h5", "B_Be5", "B_hxg4", "B_Qf5", "B_g3", 
					 "B_a2", "B_Bxf4", "END"};//Ходы белых (Player2)
    key_t id_que, id_sem;
    int msgid, semid, len_trn;
	len_trn = sizeof(turns)/sizeof(turns[0]);
    struct msgbuf msg;
	/* semaphore */
    if((id_sem = ftok("player1.c", 't')) == -1){
       perror("fail id_sem");
       exit(1);
    }
    if((semid = semget(id_sem, 2, 0666)) == -1){
        perror("semget fail");
		exit(EXIT_FAILURE);
   }
    if((id_que = ftok("player2.c", 'r')) == -1){
        perror("fail id_que");
    }
    if((msgid = msgget(id_que, 0666 | IPC_CREAT)) == -1){
        perror("fail open queue");
    }
	struct sembuf ops[2];
	ops[0].sem_num = 0;
    ops[1].sem_num = 1;
    ops[0].sem_flg = SEM_UNDO;
    ops[1].sem_flg = SEM_UNDO;
/* Отправка сообщений в очередь Player2 */
    for(int i = 0; i < len_trn; i++){
	/* Захватываем семафор 1 */
        ops[1].sem_op = -1;
		if(semop(semid, ops + 1, 1) == -1){
			perror("semop lock fail");
			
		}
        msg.type = 1;
        strcpy(msg.text, turns[i]);
        if ((msgsnd(msgid, &msg, strlen(msg.text) + 1, 0)) == -1){
            perror("fail send message");
            msgctl(msgid, IPC_RMID,  NULL);
            exit(1);
        }
		/* Освобождаем семафор 0 */
            ops[0].sem_op = 1;
		  if(semop(semid, ops, 1) == -1) {
        	perror("semop unlock (child)");
        }
    }
}
