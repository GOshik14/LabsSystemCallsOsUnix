/***********************************************************************************************************
* 8. Включить в порожденный процесс системный вызов signal, переопределяющий стандартную реакцию на сигнал
* (для внешнего цикла установить в функции максимальное значение параметра цикла).
* Что изменится?
***********************************************************************************************************/

#include <stdio.h> //void perror(const char *s);
#include <sys/types.h> // pid_t
#include <unistd.h> //pid_t fork (void); unsigned int sleep(unsigned int seconds);
#include <sys/wait.h> //pid_t wait(int *status); pid_t waitpid(pid_t pid, int *status, int options);  
#include <signal.h> // sighandler_t signal(int signum, sighandler_t handler); int kill(pid_t pid, int signo);
// typedef /* unspecified */ sig_atomic_t;
//unsigned int alarm(unsigned int seconds);

typedef void (*sighandler_t)(int);

#define MAX_OUTER_CYCLE_ITER 100
#define MIN_OUTER_CYCLE_ITER 10


volatile sig_atomic_t outer_cycle_iter = MIN_OUTER_CYCLE_ITER;

void signal_func(int sig_n) // default value - handler state to  SIG_DFL : signal(2, SIG_DFL);
{
	printf("Inside selfmade function - handler signan number %d!\n", sig_n);
	outer_cycle_iter = MAX_OUTER_CYCLE_ITER;
	signal(sig_n, signal_func); 
}

int main()
{
	pid_t pid = fork();
	
	if(pid == 0)
	{
		signal(SIGUSR2, signal_func);
		
		printf("Child process: pid = %d\n", getpid());
		printf("Child process: getppid = %d\n", getppid());
		printf("Child process: getgid = %d\n", getgid());
		printf("Child process: getegid = %d\n", getegid());
		
		for(int i = 0; i < outer_cycle_iter; i++)
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
		
		sleep(1);
		
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
