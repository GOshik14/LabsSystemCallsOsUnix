/***********************************************************************************************************
* 1. Изменить реакцию процесса на некоторый сигнал при помощи signal. 
* В функции обработчике переустановить реакцию на сигнал на значение по умолчанию. 
* Запустить программу и объяснить наблюдаемый результат.
***********************************************************************************************************/

#include <stdio.h>
#include <unistd.h> // pid_t getpid(void)

#include <signal.h> // sighandler_t signal(int signum, sighandler_t handler); int kill(pid_t pid, int signo);
typedef void (*sighandler_t)(int);

#include <unistd.h> // unsigned int sleep(unsigned int seconds);


void signal_func(int sig_n) // default value - handler stete to  SIG_DFL : signal(2, SIG_DFL);
{
	printf("Inside selfmade function - handler signan number %d!\n", sig_n);
	signal(sig_n, SIG_DFL); 
	return;
}

int main()
{
	//SIGINT = 2 <- 'Ctr+C' interrapt signal from stdin, default value - Term
	//sleep(3);
	
	signal(SIGINT, signal_func);
	
	kill(getpid(), SIGINT);
	
	sleep(10);
	
	kill(getpid(), SIGINT);
	
	sleep(100);
	
	return 0;
}
