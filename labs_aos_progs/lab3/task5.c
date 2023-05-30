/***********************************************************************************************************
* 5. Из родительского процесса послать в порожденный процесс сигнал (SIGUSR1).
* Посмотреть, какой статус будет передан в родительский процесс в этом случае.
* Сколько итераций выполнится в порожденном процессе?
***********************************************************************************************************/

#include <stdio.h> //void perror(const char *s);
#include <sys/types.h> // pid_t
#include <unistd.h> //pid_t fork (void); unsigned int sleep(unsigned int seconds);
#include <sys/wait.h> //pid_t wait(int *status); pid_t waitpid(pid_t pid, int *status, int options);  
#include <signal.h> // sighandler_t signal(int signum, sighandler_t handler); int kill(pid_t pid, int signo);
typedef void (*sighandler_t)(int);
int main()
{
	pid_t pid = fork();
	
	if(pid == 0)
	{
		printf("Child process: pid = %d\n", getpid());
		printf("Child process: getppid = %d\n", getppid());
		printf("Child process: getgid = %d\n", getgid());
		printf("Child process: getegid = %d\n", getegid());
		
		for(int i = 0; i < 100; i++)
		{
			for(int j = 0; j < 10000; j++)
			{
				sleep(0);
			}
			printf("Outer cycle's iteration № %d\n", i);
		}
		
		
		return 0;
	}
	else if(pid > 0)
	{
		int status;
		
		printf("Parent process: pid = %d\n", getpid());
		printf("Parent process: getppid = %d\n", getppid());
		printf("Parent process: getgid = %d\n", getgid());
		printf("Parent process: getegid = %d\n", getegid());
		
		//sleep(3);
		
		kill(pid, SIGUSR1);
		
		pid_t pid_child = wait(&status);
		
		if(WIFEXITED(status))
			printf("Parent: Child process pid = %d returned : %d\n", pid_child, WEXITSTATUS(status));
		else
		{
			printf("Parent: Child process pid = %d : bad ending\n", pid_child);
			
			if(WIFSIGNALED(status))
				printf("Parent: Child process pid = %d : was interrapted by signal № %d\n", pid_child, WTERMSIG(status));
		}
			
	}
	else
	{
		perror("Error fork()");
		return -1;
	}
	
	return 0;
}