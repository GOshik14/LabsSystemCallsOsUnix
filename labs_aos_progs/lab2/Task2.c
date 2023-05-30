#include <stdio.h> //void perror(const char *s);
#include <unistd.h> //pid_t fork (void);

int main()
{
	pid_t pid = fork();
	
	if(pid == 0)
	{
		printf("Child process: pid = %d\n", getpid());
	}
	else if(pid > 0)
	{
		printf("Parent process: pid = %d\n", getpid());
	}
	else
	{
		perror("Error fork()");
		return -1;
	}
	
	return 0;
}
