#include <stdio.h>
#include <unistd.h>
#include <string.h>
/**
 *1,它是半双工的（数据只能在一个方向上流动），具有固定的读端和写端
 *2,他只能用于亲缘关系的进程之间的通信
 *3,他可以看成是一个特殊的文件，对于他的读写也可以使用普通的read和write等函数，
 *但是他不是普通的文件，并不属于任何文件系统，并且只存在于内存中。
 */
int main(int argc, const char *argv[])
{
	int fd[2];
	pid_t pid;
	char rdbuff[64] = {0};
	char wrbuff[64] = "hello Beijing, good morning";

	if(pipe(fd) < 0){
		printf("Create pipe Error\n");
	}
	if((pid = fork()) < 0){
		printf("Fork Error\n");
	}
	else if(pid > 0){
		close(fd[0]);
		write(fd[1], wrbuff, sizeof(wrbuff));
	}else{
		close(fd[1]);
		read(fd[0], rdbuff, sizeof(rdbuff));
	}
	printf("%s\n", rdbuff);
	return 0;
}
