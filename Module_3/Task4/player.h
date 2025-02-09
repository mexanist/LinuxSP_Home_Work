#include <sys/types.h>
#include <sys/sem.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

struct msgbuf {
     long type;
     char text[256];
};

