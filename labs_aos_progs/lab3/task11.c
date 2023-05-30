/***********************************************************************************************************
* 11. Написать программу, позволяющую использовать sigaction для реализации примера синхронизации процессов.
* Выполнить эту программу и объяснить ее поведение. Использовать sigsuspend и sigprocmask.
***********************************************************************************************************/

#include <signal.h> // int sigprocmask(int how, const sigset_t *set, sigset_t *oldset);
#include <signal.h> // int sigsuspend(const sigset_t *mask);
//sigsuspend(): _POSIX_C_SOURCE >= 1 || _XOPEN_SOURCE || _POSIX_SOURCE
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
	
	unsigned int time_for_sleep = 0;
	if(sig_n == SIGUSR1)
		time_for_sleep = 1;
	else if(sig_n == SIGUSR2)
		time_for_sleep = 2;
	
	sleep(time_for_sleep);
	
	printf("Inside selfmade function - end of handler signan number %d, after sleep(%d)!\n", sig_n, time_for_sleep);
}

int main()
{
	pid_t pid = fork();
	
	struct sigaction  sigaction_f = {0};
	sigaction_f.sa_handler = signal_func;
	sigaction(SIGUSR1, &sigaction_f, NULL);
	sigaction(SIGUSR2, &sigaction_f, NULL);
	
	if(pid == 0)
	{
		sigset_t set, oldset;
		sigemptyset(&set);
		sigemptyset(&oldset);
		sigaddset(&set, SIGUSR1); 
		//sigaddset(&set, SIGUSR2); 
		
		sigprocmask(SIG_SETMASK, &set, &oldset);
		printf("Impotant part of code here!!!\n");
		sleep(3);
		for(int i = 0; i < outer_cycle_iter; i++)
		{
			for(int j = 0; j < 10000; j++)
			{
				sleep(0);
			}
			printf("Outer cycle's iteration № %d\n", i);
		}
		printf("End of impotant part of code!!!\n");
		sigprocmask(SIG_SETMASK, &oldset, NULL); 
		
		sigset_t mask;
		sigemptyset(&mask);
		sigaddset(&mask, SIGUSR1);
		sigsuspend(&mask);
		printf("Child process: pid = %d\n", getpid());
		printf("Child process: getppid = %d\n", getppid());
		printf("Child process: getgid = %d\n", getgid());
		printf("Child process: getegid = %d\n", getegid());
			
		return 0;
	}
	else if(pid > 0)
	{
		/*
		sigset_t set, oldset;
		sigemptyset(&set);
		sigemptyset(&oldset);
		sigaddset(&set, SIGUSR2); 
		
		sigprocmask(SIG_SETMASK, &set, &oldset);
		printf("Impotant part of code here!!!\n");
		sleep(3);
		printf("End of impotant part of code!!!\n");
		sigprocmask(SIG_SETMASK, &oldset, NULL);
		*/
		
		int status;
		
		printf("Parent process: pid = %d\n", getpid());
		printf("Parent process: getppid = %d\n", getppid());
		printf("Parent process: getgid = %d\n", getgid());
		printf("Parent process: getegid = %d\n", getegid());
		
		sleep(5);
		
		
		kill(pid, SIGUSR1);
		//printf("After the first kill(getpid(), SIGUSR1); \n");
		
		kill(pid, SIGUSR1);
		//printf("After the second kill(getpid(), SIGUSR1); \n");
		
		kill(pid, SIGUSR1);
		//printf("After 3th kill(getpid(), SIGUSR1); \n");
		
		kill(pid, SIGUSR1);
		//printf("After 4th kill(getpid(), SIGUSR1); \n");
		
		kill(pid, SIGUSR2);
		//printf("After the 5st kill(getpid(), SIGUSR2); \n");
		
		sleep(10);
		kill(pid, SIGUSR1);
		//printf("After sleep(10); kill(getpid(), SIGUSR1); \n");
		
		kill(pid, SIGUSR2);
		//printf("After sleep(10); kill(getpid(), SIGUSR2); \n");
		
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
