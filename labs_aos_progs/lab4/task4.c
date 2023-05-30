/***********************************************************************************************************
* 4. Повторить п. 2, создавая параллельные процессы с помощью связки fork - exec.
* Как передать дескрипторы канала в порожденный процесс?.
***********************************************************************************************************/

#include <stdio.h>
#include <stdlib.h> // int system(const char *s);
#include <sys/types.h> // pid_t 
#include <unistd.h> //  pid_t fork(void); int pipe(int pipefd[2]); int execl(char *name, char *arg0, ... /*NULL*/);
#include <sys/stat.h> // int mkfifo(const char *fifoname, mode_t mode);
#include <fcntl.h> /* Определение констант O_* */
#include <sys/wait.h>
#include <string.h>

int main() /// another execut file name!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!(non a.out!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!)
{	
	pid_t pid = fork();
	if(pid == 0) //child
	{
		execl("a.out", NULL);
		
		exit(0);
	}
	else if(pid > 0) //parent
	{
		printf("Empty parent process!=)\n");
	    	
		wait(NULL);
		
		printf("End empty parent process!=(\n");
		
		exit(0);
	}
	else //error fork()
	{
		perror("After fork() ");
		exit(-1);
	}

}
