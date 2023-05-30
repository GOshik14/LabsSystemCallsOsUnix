/***********************************************************************************************************
* 10. Написать программу, иллюстрирующую способ блокирования дополнительных сигналов на время работы обработчика сигнала.
* Что произойдет, если во время обработки некоторого сигнала в процесс поступит несколько однотипных
* заблокированных сигналов.
***********************************************************************************************************/

#include <stdio.h> //void perror(const char *s);
#include <sys/types.h> // pid_t
#include <unistd.h> //pid_t fork (void); unsigned int sleep(unsigned int seconds);
#include <sys/wait.h> //pid_t wait(int *status); pid_t waitpid(pid_t pid, int *status, int options);  
#include <signal.h> // sighandler_t signal(int signum, sighandler_t handler); int kill(pid_t pid, int signo);
// typedef /* unspecified */ sig_atomic_t;
//unsigned int alarm(unsigned int seconds);

typedef void (*sighandler_t)(int);

/*
struct sigaction {
    void (*sa_handler)(int);
    void (*sa_sigaction)(int, siginfo_t *, void *);
    sigset_t sa_mask;
    int sa_flags;
    void (*sa_restorer)(void);
}
*/

#define MAX_OUTER_CYCLE_ITER 100
#define MIN_OUTER_CYCLE_ITER 10


volatile sig_atomic_t outer_cycle_iter = MIN_OUTER_CYCLE_ITER;

void signal_func(int sig_n) // default value - handler stete to  SIG_DFL : signal(2, SIG_DFL);
{
	printf("Inside selfmade function - handler signan number %d!\n", sig_n);
	sleep(10);
	printf("Inside selfmade function - after sleep(10); %d!\n", sig_n);
}

int main()
{
	pid_t pid = fork();
	
	if(pid == 0)
	{
		struct sigaction  sigaction_f = {0};
		sigaction_f.sa_handler = signal_func;
	
		sigset_t   set; 
		sigemptyset(&set);                                                             
		//sigaddset(&set, SIGINT); 
		sigaddset(&set, SIGUSR1); 
		sigaddset(&set, SIGUSR2); 
		sigaction_f.sa_mask = set;
		sigaction(SIGUSR1, &sigaction_f, NULL);
		sigaction(SIGUSR2, &sigaction_f, NULL);
		
		printf("Child process: pid = %d\n", getpid());
		printf("Child process: getppid = %d\n", getppid());
		printf("Child process: getgid = %d\n", getgid());
		printf("Child process: getegid = %d\n", getegid());
		
		pause();
		
		for(int i = 0; i < outer_cycle_iter; i++)
		{
			for(int j = 0; j < 1000000; j++)
			{
				;
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
		
		sleep(5);
		
		//kill(pid, SIGINT);
	
		//printf("After kill(getpid(), SIGINT); \n");
		
		kill(pid, SIGUSR1);
	
		printf("After kill(getpid(), SIGUSR1); \n");
	
		kill(pid, SIGUSR2);
	
		printf("After kill(getpid(), SIGUSR2); \n");
	
		//kill(getpid(), SIGUSR1);
		//kill(getpid(), SIGUSR1);
		//kill(getpid(), SIGUSR2);
		//kill(getpid(), SIGUSR2);
	
		//sleep(10);
		
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
