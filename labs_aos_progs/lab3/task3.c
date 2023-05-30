/***********************************************************************************************************
* 3. Написать программу, исключающую появление зомби для завершающихся порожденных процессов.
***********************************************************************************************************/

#include <stdio.h>
#include <unistd.h> //pid_t fork (void);
#include <sys/types.h> // pid_t
#include <sys/wait.h> //pid_t wait(int *status); pid_t waitpid(pid_t pid, int *status, int options);  

int main()
{
	struct sigaction  sigaction_i = {0};
    sigaction_i.sa_handler = SIG_IGN;
	
	sigaction(SIGCHLD, &sigaction_i, NULL); 
	
	pid_t pid = fork();
	
	if(pid == 0)
	{
		printf("Child process: pid = %d\n", getpid());
		printf("Child process: getppid = %d\n", getppid());
		printf("Child process: getgid = %d\n", getgid());
		printf("Child process: getegid = %d\n", getegid());
		//sleep(3);
		return 0;
	}
	else if(pid > 0)
	{
		int status;
		
		printf("Parent process: pid = %d\n", getpid());
		printf("Parent process: getppid = %d\n", getppid());
		printf("Parent process: getgid = %d\n", getgid());
		printf("Parent process: getegid = %d\n", getegid());
		sleep(10);
		//pid_t pid_child = wait(&status);
		//printf("Parent: Child process pid = %d returned : %d\n", pid_child, WEXITSTATUS(status));
	}
	else
	{
		perror("Error fork()");
		return -1;
	}
	
	return 0;
	
	return 0;
}
