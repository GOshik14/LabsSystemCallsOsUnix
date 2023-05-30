/***********************************************************************************************************
* 6. Написать программы для работы с очередями сообщений в соответствии с моделью клиент-сервер:
* каждый процесс использует собственную очередь сообщений. Процесс-сервер читает запросы из своей очереди
* сообщений и посылает ответ процессам-клиентам в их очереди. Процессы-клиенты читают ответ и выводят его
* в выходной поток. Процессы-клиенты должны передавать процессу-серверу информацию о своих очередях сообщений
* (куда записывать ответ).
***********************************************************************************************************/

#include <stdio.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/msg.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <unistd.h> // unsigned int sleep(unsigned int seconds);

#define MSGSZ     128

typedef struct msgbuf {
         long    mtype;
         char    mtext[MSGSZ];
         } message_buf;

//#define PERROR_EXIT(reterned_value) {}

int main()
{
	//server queue - for requests from hosts 1, 2, 3
	int qid_server = msgget(911, IPC_CREAT | IPC_EXCL | 0664 );
	if(qid==-1)
	{
		perror("server prog: msgget for server failed");
		exit(1);
    }
	
	//host queue - for requests from hosts EMERGENCY
	int qid_emg = msgget(113, 0664 );
	if(qid==-1)
	{
		perror("server prog: msgget for 3-th host failed");
		exit(1);
    }
	
	//host queue - for requests from hosts POLLI
	int qid_pol = msgget(112, 0664 );
	if(qid==-1)
	{
		perror("server prog: msgget for 2-nd host failed");
		exit(1);
    }
	
	//host queue - for requests from hosts FIREMEN
	int qid_frm = msgget(111, 0664 );
	if(qid==-1)
	{
		perror("server prog: msgget for 1-nd host failed");
		exit(1);
    }
	
	
	message_buf buf[3] = {0, 0, 0};
	long msgtyp[3] = {111, 112, 113};  // msgtyp -> key of message queue
	const char *answers[3] =  { "Go to fire, FIREMEN!!!",
								"Go to place of murder!",
								"Go to ill people to cure they!!!"
							 };
	
	while(1)
	{
		for(int i = 0; i < 3; i++)
		{
			if(msgrcv(qid_server, &buf[i], MSGSZ, msgtyp[i], IPC_NOWAIT) < 0)
			{
				perror("server prog:  msgrcv");
				
				//exit(-1);
			}
			else
			{

      }
			}
		//printf("%s\n", buf[i].mtext);
	}
	
	return 0;
}
