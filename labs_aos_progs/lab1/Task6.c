#include <errno.h>
#include <fcntl.h> //flags for open()
#include <stdio.h>
#include <string.h> // char *strcpy(char *destination, const char *source); size_t strlen(const char *string);
#include <unistd.h> // int close (int fd); off_t lseek(int fildes, off_t offset, int whence);
#include <stdlib.h> // int atoi(const char *s); ssize_t read (int fd, void * buffer, size_t count);
//ssize_t write(int fildes, const void *buf, size_t nbyte);
#define STRING_SIZE 100
//unsigned long strtoul(const char *s, char **endptr, int base);

//file in the same directories: ./text.txt
//int errno - the last returned error
//const char * const sys_errlist[]; 
//extern const char * const sys_errlist[]; 

// ./a.out task6.txt 0666


int main(int argc, char *argv[]) //argv[1] - file's name, argv[2] - file's permissions -> int(0444),
{	
	const char* str[2] = {"Simple text for test writing to file. ", "Bye bye." };
	char str_buffer[100];
	
	int fid = open(argv[1], O_RDWR | O_CREAT | O_EXCL, strtoul(argv[2], NULL, 0));
	
	if(fid == -1) {
		perror("open(argv[1], O_RDWR | O_CREAT | O_EXCL, strtoul(argv[2], NULL, 0)) ");
		return -1;
	}
	
	lseek (fid, 100, SEEK_SET);
	write(fid, str[0], strlen(str[0])+1);
	read(fid, str_buffer, strlen(str[0])+1);
	printf("Print text after wirte, read: %s End of text.\n", str_buffer);
	
	lseek (fid, 100, SEEK_SET);
	read(fid, str_buffer, 100);
	printf("Print text after lseek (fid, 100, SEEK_SET); : %s End of text.\n", str_buffer);
	
	write(fid, str[1], strlen(str[1])+1);
	lseek (fid, -20, SEEK_END);
	read(fid, str_buffer, 10);
	str_buffer[10] = '\0';
	printf("Print text after lseek (fid, -20, SEEK_END); : %s End of text.\n", str_buffer);
	
	lseek (fid, 5, SEEK_CUR);
	read(fid, str_buffer, 5);
	str_buffer[10] = '\0';
	printf("Print text after lseek (fid, 5, SEEK_CUR); : %s End of text.\n", str_buffer);
	lseek (fid, 100, SEEK_SET);
	
	close(fid);
	
	return 0;
}
