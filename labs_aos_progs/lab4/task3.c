/***********************************************************************************************************
* 3. Модифицировать программу п. 2 таким образом, чтобы процессы реализовали двунаправленную связь (диалог).
***********************************************************************************************************/

#include <stdio.h>
#include <stdlib.h> // int system(const char *s);
#include <sys/types.h> // pid_t 
#include <unistd.h> //  pid_t fork(void); int pipe(int pipefd[2]);
#include <sys/stat.h> // int mkfifo(const char *fifoname, mode_t mode);
#include <fcntl.h> /* Определение констант O_* */
#include <sys/wait.h>
#include <string.h>

int main()
{
	if(mkfifo("fifo_3", 0660) == -1)
	{
		perror("mkfifo() ");
		exit(-1);
	}
	
	char str[] = "Simple text writien in parent's process, this've read by pipe in child's process\n";
	char str2[] = "Simple text writien in child's process, this've read by FIFO(named pipe) in parent's process\n";
	char buffer[128] = {0};
	
	pid_t pid = fork();
	if(pid == 0) //child
	{
		sleep(1); //wait for parent completed writing
		int r_fifo = open("fifo_3", O_RDONLY);
		if(r_fifo < 0)
		{
			perror("r_fifo = open(); ");
			exit(-1);
		}
		read(r_fifo, buffer, sizeof(buffer));
		printf("%s", buffer);
		close(r_fifo);
		
		int w_fifo = open("fifo_3", O_WRONLY);
		if(w_fifo < 0)
		{
			perror("w_fifo = open(); ");
			exit(-1);
		}
		write(w_fifo, str2, strlen(str2) + 1);
		close(w_fifo);
		
		exit(0);
	}
	else if(pid > 0) //parent
	{
		int w_fifo = open("fifo_3", O_WRONLY);
		if(w_fifo < 0)
		{
			perror("w_fifo = open(); ");
			exit(-1);
		}
		write(w_fifo, str, strlen(str) + 1);
		close(w_fifo);
		
		int r_fifo = open("fifo_3", O_RDONLY);
		if(r_fifo < 0)
		{
			perror("r_fifo = open(); ");
			exit(-1);
		}
		wait(NULL);
		read(r_fifo, buffer, sizeof(buffer));
		printf("%s", buffer);
		close(r_fifo);
		
		system("rm -f fifo_3");
		
		exit(0);
	}
	else //error fork()
	{
		perror("After fork() ");
		exit(-1);
	}

}
