#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <string.h>
#include <fcntl.h>

int main(){
	int fd;
	ssize_t read_byte;
	char buf[256];
	fd = open("/tmp/fifo_signal", O_RDONLY);
	if (fd == -1){
		perror("fifo open failure");
		exit(EXIT_FAILURE);
	}
	read_byte = read(fd, buf, sizeof(buf) - 1);
	if(read_byte == -1){
		perror("read buf failure");
		exit(EXIT_FAILURE);
	}
	buf[read_byte] = '\0';
	printf("%s\n", buf);
	if(close(fd) == -1){
		perror("fifo close failure");
		exit(EXIT_FAILURE);
	}
}
