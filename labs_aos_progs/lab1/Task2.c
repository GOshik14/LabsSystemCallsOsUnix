#include <errno.h>
#include <fcntl.h> //flags for open()
#include <stdio.h>
#include <string.h> // char *strcpy(char *destination, const char *source); size_t strlen(const char *string);
#include <unistd.h> // int close (int fd); 
#include <stdlib.h> // int atoi(const char *s); ssize_t read (int fd, void * buffer, size_t count);
//ssize_t write(int fildes, const void *buf, size_t nbyte);
#define STRING_SIZE 100
//unsigned long strtoul(const char *s, char **endptr, int base);

//file in the same directories: ./text.txt
//int errno - the last returned error
//const char * const sys_errlist[]; 
//extern const char * const sys_errlist[]; 

// ./a.out task2.txt 0444

int main(int argc, char *argv[]) //argv[1] - file's name, argv[2] - file's permissions -> int(0444),
{
	//if(agrc < 3 && argv[1])
	const char* str[2] = {"Simple text for test writing to file. ", "End. Bye bye." };
	char str_buffer[100];
	
	int fid = open(argv[1], O_RDWR | O_CREAT | O_EXCL, strtoul(argv[2], NULL, 0));
	//perror("open(argv[1], O_RDWR | O_CREAT | O_EXCL, strtoul(argv[2], NULL, 0));");
	if(fid == -1) {
		perror("open(argv[1], O_RDWR | O_CREAT | O_EXCL, strtoul(argv[2], NULL, 0)) ");
		return -1;
	}
	
	write(fid, str[0], strlen(str[0]));
	write(fid, str[1], strlen(str[1]) + 1);
	close(fid);
	
	fid = open(argv[1], O_RDONLY, atoi(argv[2]));
	read(fid, str_buffer, 100);
	//perror("read(fid, str_buffer, 100); ");
	printf("%s\n", str_buffer);
	close(fid);
	
	fid = open(argv[1], O_RDWR);
	perror("Open O_RDWR file 0444: ");
	close(fid);
	
	return 0;
}
