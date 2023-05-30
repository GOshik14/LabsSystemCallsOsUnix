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
	
	return file_len;	
}

int main(int argc, char *argv[]) //argv[1] - file's name, argv[2] - file's permissions -> int(0444),
{	
	if(argc == 1)
	{
		printf("Bad command format!\n");
		return -1;
	}
	
	int count_files = argc - 1;
	int max_len = -1;
	
	for(int i = 1; i <= count_files; i++)
	{
		int fd = open(argv[i], O_RDONLY);
		if(fd < 0 )
		{
			printf("Bad file's name format : %s!\n", argv[i]);
			perror("Error");
			return -2;
		}
		
		int length_file = len_file(fd);
		
		if(length_file > max_len)
			max_len = length_file;			
		
		
		close(fd);
	}

    printf("Max file's length: %d\n", max_len);

	return 0;
}