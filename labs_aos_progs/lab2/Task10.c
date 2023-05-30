#include <stdlib.h> // int system(const char *s);
#include <stdio.h> // perror(const char *s);
#include <string.h> //sprintf
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <unistd.h> // pid_t fork(void); int close (int fd); off_t lseek(int fildes, off_t offset, int whence);
//ssize_t read (int fd, void * buffer, size_t count);
//ssize_t write (int fd, const void * buffer, size_t count);
//unsigned int sleep(unsigned int seconds);
//int execv(char *name, char *argv[]);
// int execlp(const char *file, const char *arg, ... /* (char  *) NULL */);

// env > env.txt //create file with environment info =)

int main(int argc, char *argv[])
{
	//char *prog_exec = argv[1];
	
	if(argc != 3)
	{
		printf("Bad comand's line arguments! Try again.\n");
		return -1;
	}
	
	//int fd_common = open(argv[1], O_RDONLY);
	
	pid_t pid = fork();
	
	int i = 0;
	if(pid == 0) //child ps
	{
		//int i = 0;
		while(argv[++i] != NULL)
            printf("%s \n",argv[i]);
		
		system("env");
		 
		//char *argv[3] = {prog_exec, }; 
		execl(argv[1], argv[1], argv[2], NULL ); //task9 t8
		
		return 0;
	}
	else if( pid > 0) //parent ps
	{
		//int i = 0;
		while(argv[++i] != NULL)
            printf("%s \n",argv[i]);
		
		system("env");
		wait(NULL);
		return 0;
	}
	else
	{
		printf("Cann't fork main process!\n");
		return -2;
	}

}
