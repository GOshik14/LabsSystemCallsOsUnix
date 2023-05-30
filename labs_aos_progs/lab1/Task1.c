#include <errno.h>
#include <fcntl.h> //flags for open()
#include <stdio.h>
#include <string.h> //char *strerror(int errcode);
#include <stdlib.h> // int system(const char *s);
#include <unistd.h> // int close (int fd);

//file in the same directories: ./text.txt
//int errno - the last returned error
//const char * const sys_errlist[]; 
//extern const char * const sys_errlist[]; 

int main() //
{
	//Task1
	int last_errno = 0;
	
	system("touch ./forTask1.txt");
	int fid = open("./forTask1.txt", O_RDWR);
	last_errno = errno;
	printf("fid = %d\n", fid);
	
	//errno
	printf("The last errno = %d\n", last_errno);
	//printf("sys_errlist[last_errno] = %s\n", sys_errlist[last_errno]);
	printf("strerror(last_errno): %s\n", strerror(last_errno));
	perror("perror() ");
	
	fid = open("./forTask1_bad.txt", O_RDWR);
	last_errno = errno;
	printf("fid = %d\n", fid);
	
	//errno
	printf("The last errno = %d\n", last_errno);
	//printf("sys_errlist[last_errno] = %s\n", sys_errlist[last_errno]);
	printf("strerror(last_errno): %s\n", strerror(last_errno));
	perror("perror() ");
	
	close (fid);
	
	return 0;
}
