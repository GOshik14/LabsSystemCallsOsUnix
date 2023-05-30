#include <stdio.h>
#include <pthread.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>
#include <sched.h>



void signal_func(int sig_n)
{
	printf("Inside selfmade function - handler signan number %d!\n", sig_n);
	printf("PosixProcess PID = %d Thread TID %ld is running.\n", getpid(), pthread_self());
	printf("Inside selfmade function: end of function - handler signan number %d!\n", sig_n);

	return;
}

int inf_async_cancel()
{
	printf("PosixProcess PID = %d (function inf_async_cancel ) Thread TID %ld is running.\n", getpid(), pthread_self());
	
	int err = 0;


	sigset_t set;

	err = sigemptyset(&set);
	if(err)
	{
		perror("sigemptyset(&set)");
		return err;
	}
	
	err = sigaddset(&set, SIGUSR1);
	if(err)
	{
		perror("sigaddset(&set, SIGUSR1)");
		return err;
	}
	
	err = pthread_sigmask(SIG_BLOCK, &set, NULL);
    if(err)
	{
		printf("pthread_sigmask(SIG_SETMASK, &set, NULL); returned: %s\n", strerror(err));
		return err;
	}
		
    int oldstate = 0;
    err = pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, &oldstate);
	if(err)
	{
		printf("pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, &oldstate) returned: %s\n", strerror(err));
		return err;
	}	
	
    int oldtype = 0;
    err = pthread_setcanceltype(PTHREAD_CANCEL_ASYNCHRONOUS, &oldtype);
	if(err)
	{
		printf("pthread_setcanceltype( PTHREAD_CANCEL_ASYNCHRONOUS, &oldtype)  returned: %s\n", strerror(err));
		return err;
	} 
	
	int policy = 0;
	struct sched_param param = {0};
	err = pthread_getschedparam(pthread_self(), &policy, &param);
	if(err)
	{
		printf("pthread_getschedparam(pthread_self(), &policy, NULL);  returned: %s\n", strerror(err));
		return err;
	}
	printf("policy = %d\n", policy);	
	
	printf("PosixProcess PID = %d Thread TID %ld is running: end of initialization.\n", getpid(), pthread_self());
	
	int c = 0;
    while(1)
	{
		c++;
        c %= 100;
		//sched_yield();
	}
	
	    return 0;
}

int inf_cancel_point()
{
	printf("PosixProcess PID = %d (function inf_cancel_point ) Thread TID %ld is running.\n", getpid(), pthread_self() );
	
	int err = 0;
	
	sigset_t set;
	
	err = sigemptyset(&set);
	if(err)
	{
		perror("sigemptyset(&set)");
		return err;
	}
	
	err = sigaddset(&set, SIGUSR1);
	if(err)
	{
		perror("sigaddset(&set, SIGUSR1)");
		return err;
	}
	
	err = pthread_sigmask(SIG_UNBLOCK, &set, NULL); 
    if(err)
	{
		printf("pthread_sigmask(SIG_SETMASK, &set, NULL); returned: %s\n", strerror(err));
		return err;
	}
	
    int oldstate = 0;
    err = pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, &oldstate);
	if(err)
	{
		printf("pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, &oldstate) returned: %s\n", strerror(err));
		return err;
	}
	
    int oldtype = 0;
    err = pthread_setcanceltype( PTHREAD_CANCEL_DEFERRED , &oldtype);
	if(err)
	{
		printf("pthread_setcanceltype( PTHREAD_CANCEL_ASYNCHRONOUS, &oldtype)  returned: %s\n", strerror(err));
		return err;
	} 
	/////
	int policy = 0;
	struct sched_param param = {0};
	err = pthread_getschedparam(pthread_self(), &policy, &param);
	if(err)
	{
		printf("pthread_getschedparam(pthread_self(), &policy, NULL);  returned: %s\n", strerror(err));
		return err;
	}
	printf("policy = %d\n", policy);
	
	printf("PosixProcess PID = %d Thread TID %ld is running: end of initialization.\n", getpid(), pthread_self());	
	
	int c = 0;
    while(1)
	{
		c++;
        c %= 100;
		pthread_testcancel();
		//sched_yield();
	}
	
	return 0;
}

int main()
{
	printf("Process main : PID = %d\n", getpid());
	
	printf("sizeof(pthread_self()) = %d\n",  sizeof(pthread_self()));
	long int l = 0;
	printf("sizeof(l) = %d\n",  sizeof(l));
	
	
	int policy = 0;
	struct sched_param param = {0};
	int	err = pthread_getschedparam(pthread_self(), &policy, &param);
	if(err)
	{
		printf("pthread_getschedparam(pthread_self(), &policy, &param);  returned: %s\n", strerror(err));
		return err;
	}
	printf("policy = %d\n", policy);
	
	
	err = pthread_setschedparam(pthread_self(), SCHED_OTHER, &param);
	if(err)
	{
		printf("pthread_setschedparam(pthread_self(), SCHED_RR, &param));  returned: %s\n", strerror(err));
		return err;
	}
	
	err = pthread_getschedparam(pthread_self(), &policy, &param);
	if(err)
	{
		printf("pthread_getschedparam(pthread_self(), &policy, &param);  returned: %s\n", strerror(err));
		return err;
	}
	printf("After pthread_setschedparam(pthread_self(), SCHED_RR, NULL); -> policy = %d\n", policy);
	
	printf("Main: PosixProcess PID = %d Thread TID %ld is running.\n", getpid(), pthread_self() );
	
	printf("SCHED_FIFO = %d\n", SCHED_FIFO);
	printf("SCHED_RR = %d\n", SCHED_RR);
	printf("SCHED_OTHER = %d\n", SCHED_OTHER);
	
	
	struct sigaction  sigaction_f = {0};
    sigaction_f.sa_handler = signal_func;
	
	err = sigemptyset(&sigaction_f.sa_mask);
	if(err)
	{
		perror("sigemptyset(&sigaction_f.sa_mask)");
		return err;
	}
	
	err = sigaddset(&sigaction_f.sa_mask, SIGUSR1);
	if(err)
	{
		perror("sigaddset(&sa_mask, SIGUSR1)");
		return err;
	}	
	sigaction(SIGUSR1, &sigaction_f, NULL);
	
	sigset_t set;
	err = sigemptyset(&set);
	if(err)
	{
		perror("sigemptyset(&set)");
		return err;
	}
	
	err = sigaddset(&set, SIGUSR1);
	if(err)
	{
		perror("sigaddset(&set, SIGUSR1)");
		return err;
	}

	
	err = sigprocmask(SIG_BLOCK, &set, NULL);
	if(err)
	{
		printf("sigprocmask(SIG_SETMASK, &set, NULL); returned: %s\n", strerror(err));
		return err;
	}
	
	pthread_t th1 = 0;
	pthread_t th2 = 0;
	
	pthread_attr_t attr;
	err = pthread_attr_init(&attr);
	if(err)
	{
		printf("pthread_attr_init(&attr); returned: %s\n", strerror(err));
		return err;
	}
	
	err = pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
	if(err)
	{
		printf("pthread_attr_init(&attr); returned: %s\n", strerror(err));
		return err;
	}
	
	//32768
	err = pthread_attr_setstacksize(&attr, 32768);
    if(err)
	{
		printf("pthread_attr_setstacksize (&attr, 32768); returned: %s\n", strerror(err));
		return err;
	}
	
	
	err = pthread_attr_setschedpolicy(&attr, SCHED_RR);
	if(err)
	{
		printf("pthread_attr_setschedpolicy(&attr, SCHED_RR); returned: %s\n", strerror(err));
		return err;
	}
	
	sleep(3);
	
	
	err = pthread_create(&th1, &attr, (void * (*)(void *))inf_async_cancel, NULL);
	if(err)
	{
		printf("pthread_create(&th1, &attr, inf_async_cancel, NULL); returned: %s\n", strerror(err));
		return err;
	}
	
	sleep(3);
	
	err = pthread_create(&th2, &attr, (void * (*)(void *))inf_cancel_point, NULL);
	if(err)
	{
		printf("pthread_create(&th2, &attr, inf_cancel_point, NULL) returned: %s\n", strerror(err));
		return err;
	}
	
	sleep(3);
	
	pthread_kill(th1,SIGUSR1);
	
	sleep(3);
	
	pthread_kill(th2,SIGUSR1);
		
	while(1);

	
	return 0;
}

