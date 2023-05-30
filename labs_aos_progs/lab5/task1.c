/***********************************************************************************************************
* 1. Создать очередь сообщений или получить доступ к уже существующей очереди. Вывести на экран
* статистическую информацию об очереди сообщений. Поместить несколько сообщений различных типов в очередь.
***********************************************************************************************************/

#include <stdio.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/msg.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

/* Структура записи для одного сообщения в области ядра
Тип __time_t соответствует типу long int.
Все данные типы определены в заголовочном файле types.h*/
//struct msqid_ds
//{
//struct ipc_perm msg_perm; /* структура описывает права доступа */
//__time_t msg_stime;       /* время последней команды msgsnd (см. ниже) */
//unsigned long int __unused1;
//__time_t msg_rtime;       /* время последней команды msgrcv (см. ниже) */
//unsigned long int __unused2;
//__time_t msg_ctime;       /* время последнего изменения */
//unsigned long int __unused3;
//unsigned long int __msg_cbytes; /* текущее число байт в очереди */
//msgqnum_t msg_qnum;      /* текущее число сообщений в очереди */
//msglen_t msg_qbytes;     /* максимальный размер очереди в байтах */
//__pid_t msg_lspid;       /* pid последнего процесса вызвавшего msgsnd() */
//__pid_t msg_lrpid;       /* pid последнего процесса вызвавшего msgrcv() */
//unsigned long int __unused4;
//unsigned long int __unused5;
//};

//int msgsnd (int msqid, const void *msgp, size_t msgsz, int msgflg);

//#undef _POSIX_SOURCE
//#include <sys/capability.h>
//int capget(cap_user_header_t hdrp, cap_user_data_t datap);

//int capset(cap_user_header_t hdrp, const cap_user_data_t datap);  

/*typedef struct __user_cap_header_struct {
   __u32 version;
   int pid;
} *cap_user_header_t;

typedef struct __user_cap_data_struct {
   __u32 effective;
   __u32 permitted;
   __u32 inheritable;
} *cap_user_data_t;*/

#define MSGSZ     128

typedef struct msgbuf {
         long    mtype;
         char    mtext[MSGSZ];
         } message_buf;

int main()
{
    int qid = msgget(14, IPC_CREAT | 0664 );
	
	if(qid==-1){
		perror("msgget failed");
		exit(1);
    }
    
    struct msqid_ds qstatus = {0};
	
	if(msgctl(qid,IPC_STAT,&qstatus)<0)
	{
		perror("msgctl failed");
		exit(1);
    }
	
	printf("текущее число байт в очереди %d\n", qstatus.msg_stime);
	printf("текущее число сообщений в очереди %d\n", qstatus.msg_qnum);
	printf("время последнего изменения %s\n", ctime(&(qstatus.msg_ctime)));
	
	printf("Real user id of the queue creator: %d\n",qstatus.msg_perm.cuid);
    printf("Real group id of the queue creator: %d\n",qstatus.msg_perm.cgid);

    printf("Effective user id of the queue creator: %d\n",qstatus.msg_perm.uid);
    printf("Effective group id of the queue creator: %d\n",qstatus.msg_perm.gid);
    printf("Permissions: %d\n",qstatus.msg_perm.mode);
    printf("Message queue id: %d\n",qid);
    printf("%d message(s) on queue\n",qstatus.msg_qnum);
    printf("Last message sent by process :%3d at %s \n",qstatus.msg_lspid,ctime(& (qstatus.msg_stime)));

    printf("Last message received by process :%3d at %s \n",qstatus.msg_lrpid,ctime(& (qstatus.msg_rtime)));
    printf("Current number of bytes on queue %d\n",qstatus.msg_cbytes);
    printf("Maximum number of bytes allowed on the queue%d\n",qstatus.msg_qbytes);
	
	printf("Another way - ipcs -q:\n");
	system("ipcs -q");
	
	message_buf sbuf = {0};
	sbuf.mtype = 1;
	strcpy(sbuf.mtext, "I am in the queue?");
	
	size_t buf_length = strlen(sbuf.mtext) + 1 ;
	if(msgsnd (qid, &sbuf, buf_length, IPC_NOWAIT) < 0) {
       printf ("%d, %d, %s, %d\n", qid, sbuf.mtype, sbuf.mtext, buf_length);
       perror("msgsnd");
       exit(1);
    }
		
	
	sbuf.mtype = 2;
	strcpy(sbuf.mtext, "Yes, i am.");
	
	buf_length = strlen(sbuf.mtext) + 1 ;
	if(msgsnd (qid, &sbuf, buf_length, IPC_NOWAIT) < 0) {
       printf ("%d, %d, %s, %d\n", qid, sbuf.mtype, sbuf.mtext, buf_length);
       perror("msgsnd");
       exit(1);
    }
	sbuf.mtype = 3;
	strcpy(sbuf.mtext, "123456");
	
	buf_length = strlen(sbuf.mtext) + 1 ;
	if(msgsnd (qid, &sbuf, buf_length, IPC_NOWAIT) < 0) {
       printf ("%d, %d, %s, %d\n", qid, sbuf.mtype, sbuf.mtext, buf_length);
       perror("msgsnd");
       exit(1);
    }
	
	if(msgctl(qid,IPC_STAT,&qstatus)<0)
	{
	perror("msgctl failed");
	exit(1);
    }
	
	printf("текущее число байт в очереди %d\n", qstatus.__msg_cbytes);
	printf("текущее число сообщений в очереди %d\n", qstatus.msg_qnum);
	printf("время последнего изменения %s\n", ctime(&(qstatus.msg_ctime)));
	

	printf("Another way - ipcs -q:\n");
	system("ipcs -q");

    return 0;
}
