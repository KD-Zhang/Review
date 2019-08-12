#include <sys/stat.h>
#include <stdio.h>
#include <fcntl.h>
#include <time.h>
#include <stdlib.h>
/**
 *1,fifo可以在无关的进程之间交换数据，与pipe不同
 *2,fifo有路径名与之关联，他以一种特殊的设备文件存在与文件系统中
 */
int main(int argc, const char *argv[])
{
	int fd;
	int i, n;
	char buf[1024];
	time_t tp;

	printf("I am %d process\n", getpid());

	if((fd = open("fifo1", O_WRONLY)) < 0){
		perror("Open Filo failed");
		exit(1);
	}
	for(i = 0; i < 10; i++){
		time(&tp);
		n = sprintf(buf, "process %d's time is %s", getpid(),ctime(&tp));
		printf("send messge: %s, buf");
		if(write(fd, buf, n + 1) < 0){
			perror("write fifo failed");
			close(fd);
			exit(1);
		}
		sleep(1);
	}
	close(fd); 
	return 0;
}
