/***********************************************************************************************************
* 5. С помощью системных вызовов pipe и dup реализовать конвейер: who | wc -l.
***********************************************************************************************************/

#include <stdio.h>
#include <sys/types.h> // pid_t 
#include <unistd.h> //  pid_t fork(void); int pipe(int pipefd[2]); int close(int fd);
#include <stdlib.h>
#include <wait.h>

int main()
{
	int status;
	
	pid_t pid = fork();
	
	if(pid < 0)
	{
		perror("fork() - 1-st call");
		exit(-1);
	}
	else if(pid == 0) //children
	{
			int fd[2];
			pipe(fd);
			pid_t pid = fork();
			if(pid < 0)
			{
				perror("fork() - 2-st call");
				exit(-1);
			}
			else if(pid == 0) //children2
			{
				
				close(0);
				dup(fd[0]);
				close(fd[0]);
				close(fd[1]);

				execl("/usr/bin/wc", "wc", "-l", NULL);
				exit(0);
			}
			else // sub-parent -> children 1
			{
				close(1);
				dup(fd[1]);
				close(fd[1]);
				close(fd[0]);	
				execl("/usr/bin/who", "who", NULL);
				wait(&status);
				exit(0);
			}
		
	}
	else // parent
	{
		wait(&status);
	}
	
	
	return 0;
}
