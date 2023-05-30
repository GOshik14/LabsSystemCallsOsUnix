/***********************************************************************************************************
* 7. Повторить выполнение предыдущих пунктов задания,
* используя в порожденном процессе вместо вложенных циклов системный вызов pause.
* Что изменится? Как завершить процесс в случае выполнения с pause п. 4?
***********************************************************************************************************/

#include <stdio.h> //void perror(const char *s);
#include <sys/types.h> // pid_t
#include <unistd.h> //pid_t fork (void); unsigned int sleep(unsigned int seconds); int pause(void); 
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
		
		pause();
		
		return 0;
	}
	else if(pid > 0)
	{
		int status;
		
		printf("Parent process: pid = %d\n", getpid());
		printf("Parent process: getppid = %d\n", getppid());
		printf("Parent process: getgid = %d\n", getgid());
		printf("Parent process: getegid = %d\n", getegid());
		
		sleep(3);
		
		kill(pid, SIGUSR2);
		
		pid_t pid_child = wait(&status);
		printf("Parent: Child process pid = %d returned : %d\n", pid_child, WEXITSTATUS(status));
	}
	else
	{
		perror("Error fork()");
		return -1;
	}
	
	return 0;
}