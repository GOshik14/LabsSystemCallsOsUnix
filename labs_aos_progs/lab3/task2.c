/***********************************************************************************************************
* 2. Модифицировать программу п.1 так, чтобы вместо signal использовать sigaction.
***********************************************************************************************************/

#include <stdio.h>
#include <unistd.h> // pid_t getpid(void)

#include <signal.h> // sighandler_t signal(int signum, sighandler_t handler); int kill(pid_t pid, int signo);
typedef void (*sighandler_t)(int);

#include <unistd.h> // unsigned int sleep(unsigned int seconds);
// int sigaction(int signum, const struct sigaction *act, struct sigaction *oldact);

/*
struct sigaction {
    void (*sa_handler)(int);
    void (*sa_sigaction)(int, siginfo_t *, void *);
    sigset_t sa_mask;
    int sa_flags;
    void (*sa_restorer)(void);
}
*/

void signal_func(int sig_n) // default value - handler stete to  SIG_DFL : signal(2, SIG_DFL);
{
	printf("Inside selfmade function - handler signan number %d!\n", sig_n);
	
	struct sigaction  sigaction_i = {0};
    sigaction_i.sa_handler = SIG_DFL;
	sigaction(sig_n, &sigaction_i, NULL);
	 
	return;
}





int main()
{
	//SIGINT = 2 <- 'Ctr+C' interrapt signal from stdin, default value - Term
	
	struct sigaction  sigaction_f = {0};
    sigaction_f.sa_handler = signal_func;
	sigaction(SIGINT, &sigaction_f, NULL);
	
	kill(getpid(), SIGINT);
	
	sleep(10);
	
	kill(getpid(), SIGINT);
	
	sleep(100);
	
	return 0;
}
