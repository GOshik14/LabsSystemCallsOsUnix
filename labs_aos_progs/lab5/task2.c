/***********************************************************************************************************
* 2. Написать программу, позволяющую читать сообщения из очереди и выводить их на экран.
* Идентификатор очереди и тип сообщения передается через аргументы командной строки.
***********************************************************************************************************/

#include <stdio.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/msg.h>
#include <stdlib.h>
#include <stddef.h>
#include <time.h>
#include <string.h>

#define MSGSZ     128

typedef struct msgbuf {
         long    mtype;
         char    mtext[MSGSZ];
         } message_buf;
//int msgrcv (int msqid, void *msgp, size_t msgsz, long msgtyp, int msgflg);
//long strtol(const char *s, char **endptr, int base);

int main(int argc, char *argv[]) //./task2 14 1 2 3
{
	printf("argc = %d\n", argc);
	if(argc < 5)
	{
		printf("Too few arguments try again!!!\n");
		exit(-1);
	}
	message_buf buf[3] = {0, 0, 0};
	
	key_t key = atoi(argv[1]);
	long msgtyp[3] = {strtol(argv[2], NULL, 10), strtol(argv[3], NULL, 10), strtol(argv[4], NULL, 10)};
	

	int qid = msgget(key, NULL);
	if(qid < 0)
	{
		perror("msgget");
		exit(-1);
	}
	
	for(int i = 0; i < 3; i++)
	{
		if(msgrcv(qid, &buf[i], MSGSZ, msgtyp[i], 0) < 0)
		{
			perror("msgrcv");
			exit(-1);
		}
		printf("%s\n", buf[i].mtext);
	}
	
	return 0;
}
