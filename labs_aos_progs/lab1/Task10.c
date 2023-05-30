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

// ./a.out <existed_file_name_source> <existed_file_name_dest>

#define BUFF_SIZE 100

int len_file(const int fd_src)
{
	char buff[BUFF_SIZE] = {0};
	
	int read_bytes = 0;
	int file_len = 0;
	
	while((read_bytes = read(fd_src, buff, BUFF_SIZE)) > 0)
	{
			file_len += read_bytes;
	}
	
	if(read_bytes < 0)
	{
			fprintf(stderr, "Can't read file \n");
			return -2;
	}
	
	return file_len -1 ;	
}

int main(int argc, char *argv[]) //argv[1] - file's name, argv[2] - file's permissions -> int(0444),
{	
	int fd = open(argv[1], O_RDONLY);
	int len = len_file(fd);
	printf("len of file: %d.\n", len);
	
	char ch = '\0';
	int read_ch = 0;
	ssize_t setoff_end = 1;
	
	lseek (fd, -1, SEEK_END);
	while((read_ch = read(fd, &ch, 1)) > 0  && setoff_end <= len + 1 )
	{	
			if(ch == '\n')
			{
				lseek (fd, -(++setoff_end), SEEK_END);
				continue;
			}
			write(1, &ch, 1);
			lseek (fd, -2, SEEK_CUR);
			lseek (fd, -(++setoff_end), SEEK_END);

	}
	
	ch = '\n';
	write(1, &ch, 1);
	
	close(fd);
	
	return 0;
}