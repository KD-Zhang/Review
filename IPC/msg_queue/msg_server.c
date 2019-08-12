#include <stdio.h>
#include <stdlib.h>
#include <sys/sem.h>
#include <sys/sem.h>
/*
   1, 创建或获取一个信号量组：若成功返回信号量集ID，失败返回-1
   int semget(key_t key, int num_sems, int sem_flags);
   2, 对信号量组进行操作，改变信号量的值：成功返回0，失败返回-1
   int semop(int semid, struct sembuf semoparray[], size_t numops);
   struct sembuf 
   {
   short sem_num; // 信号量组中对应的序号，0～sem_nums-1
   short sem_op;  // 信号量值在一次操作中的改变量
   short sem_flg; // IPC_NOWAIT, SEM_UNDO
   }
   3, 控制信号量的相关信息
   int semctl(int semid, int sem_num, int cmd, ...);*/
union semun{
	int val;/*for SETVAL*/
	struct semid_ds* buf;
	unsigned short* array;
}//用于semctl
/*信号量初始化*/
int init_sem(int sem_id, int value){
	union semun temp;
	temp.val = value;
	if(semctl(sem_id, 0, SETVAL, temp) == -1){
		perror("init semaphore error");
		return -1;
	}
	return 0;
}


