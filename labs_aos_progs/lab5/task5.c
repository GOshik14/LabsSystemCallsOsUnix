/***********************************************************************************************************
* 5. Написать программу, позволяющую удалять очереди сообщений по идентификатору.
* Обработать возможные ошибочные ситуации.
***********************************************************************************************************/

#include <stdio.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/msg.h>
#include <stdlib.h> //system(const char *)
#include <time.h>
#include <string.h>

int main(int argc, char *argv[]) //14
{
	system("ipcs -q");
	
	if(argc < 2)
	{
		printf("Too few arguments try again!!!\n");
		exit(-1);
	}
	
	for(int i = 1; i < argc; i++)
	{
		key_t key = atoi(argv[i]);
		
		
	
		int qid = msgget(key, IPC_CREAT | 0664 );
		//printf("key = %d, qid = %d", key, qid);
		if(qid==-1){
			perror("msgget failed");
			//exit(1);
		}
		
		//struct msqid_ds qstatus = {0};
	
		if(msgctl(qid,IPC_RMID ,NULL) < 0)
		{
			perror("msgctl failed");
			printf("There're not queues whith  key %d\n", key);
			//exit(1);
		}
	}
	
	system("ipcs -q");

	return 0;
}
