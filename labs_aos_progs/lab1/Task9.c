#include <errno.h>
#include <fcntl.h> //flags for open()
#include <stdio.h>
#include <string.h> // char *strcpy(char *destination, const char *source); size_t strlen(const char *string);
#include <unistd.h> // int close (int fd); off_t lseek(int fildes, off_t offset, int whence); int dup2(int oldfd, int newfd);
#include <stdlib.h> // int atoi(const char *s); ssize_t read (int fd, void * buffer, size_t count);
//ssize_t write(int fildes, const void *buf, size_t nbyte);
#define STRING_SIZE 100
//unsigned long strtoul(const char *s, char **endptr, int base);

//file in the same directories: ./text.txt
//int errno - the last returned error
//const char * const sys_errlist[]; 
//extern const char * const sys_errlist[]; 

// ./a.out <existed_file_name_source> <existed_file_name_dest>

#define BUFF_SIZE 10

int file_copy(const int fd_src, const int fd_dst)
{
	char buff[BUFF_SIZE] = {0};
	
	int read_bytes = 0;
	int written_bytes_step = 0;
	int written_bytes= 0;
	
	while((read_bytes = read(fd_src, buff, BUFF_SIZE)) > 0)
	{
		//printf("read_bytes = %d\n", read_bytes);
		written_bytes_step = write(fd_dst, buff, read_bytes);
		//printf("written_bytes_step = %d\n", written_bytes_step);
		if(written_bytes_step != read_bytes)
		{
			fprintf(stderr, "Can't write file \n");
			return -1;
		}
		
		written_bytes += written_bytes_step;
	}
	
	if(read_bytes < 0)
	{
			fprintf(stderr, "Can't read file \n");
			return -2;
	}
	
	return written_bytes;	
}

//stdinput 0, stdout 1
int main(int argc, char *argv[]) //argv[1] - file's name, argv[2] - file's permissions -> int(0444),
{	
	//int fd_src = open(argv[1], O_RDONLY);
	//printf("fd_src = %d\n", fd_src);
	//dup2(0, fd_src);
	close(0);
	int fd_src = open(argv[1], O_RDONLY);
	//printf("fd_src = %d\n", fd_src);
	
	
	//int fd_dst = open(argv[2], O_WRONLY );
	//printf("fd_dst = %d\n", fd_dst);
	//dup2(1, fd_dst);
	close(1);
	int fd_dst = open(argv[2], O_WRONLY);
	//printf("fd_dst = %d\n", fd_dst);
	//lseek();
	
	file_copy(0, 1);
	
	/*
	if(argc == 1)
	{
		file_copy(0, 1);
	}
	else if(argc == 3)
	{
		int fd_src = open(argv[1], O_RDONLY);
	    if(fd_src < 0) 
	    {
			perror("Error open source file: ");
			return -3;
		}
	
		int fd_dst = open(argv[2], O_WRONLY );
		if(fd_dst < 0) 
		{
			perror("Error open destination file: ");
			return -4;
		}
		
		file_copy(fd_src, fd_dst);
	}
	else
	{
		printf("Bad command's line arguments!!!\n");
		return -5;
	}
/*
	const char* str[2] = {"Simple text for test writing to file. ", "Bye bye." };
	char str_buffer[100];
	
	int fid = open(argv[1], O_RDWR | O_CREAT | O_EXCL, strtoul(argv[2], NULL, 0));
	//perror("open(argv[1], O_RDWR | O_CREAT | O_EXCL, strtoul(argv[2], NULL, 0));");
	if(fid == -1) {
		perror("open(argv[1], O_RDWR | O_CREAT | O_EXCL, strtoul(argv[2], NULL, 0)) ");
		return -1;
	}
	
	lseek (fid, 100, SEEK_SET);
	write(fid, str[0], strlen(str[0])+1);
	//perror("write(fid, str[0], strlen(str[0])+1); ");
	read(fid, str_buffer, strlen(str[0])+1);
	//perror("read(fid, str_buffer, strlen(str[0])+1); ");
	printf("Print text after wirte, read: %s End of text.\n", str_buffer);
	
	//lseek (fid, -(100 + strlen(str[0])+1), SEEK_CUR);
	lseek (fid, 100, SEEK_SET);
	//perror("lseek (fid, 0, SEEK_SET); ");
	read(fid, str_buffer, 100);
	//perror("read(fid, str_buffer, strlen(str[0])+1); ");
	printf("Print text after lseek (fid, 100, SEEK_SET); : %s End of text.\n", str_buffer);
	
	//lseek (fid, 10, SEEK_CUR);
	write(fid, str[1], strlen(str[1])+1);
	//perror("write(fid, str[0], strlen(str[0])+1); ");
	lseek (fid, -20, SEEK_END);
	//perror("lseek (fid, -20, SEEK_END); ");
	read(fid, str_buffer, 10);
	//perror("lseek (fid, -20, SEEK_END); ");
	str_buffer[10] = '\0';
	printf("Print text after lseek (fid, -20, SEEK_END); : %s End of text.\n", str_buffer);
	
	lseek (fid, 5, SEEK_CUR);
	//perror("lseek (fid, -20, SEEK_END); ");
	read(fid, str_buffer, 5);
	//perror("lseek (fid, -20, SEEK_END); ");
	str_buffer[10] = '\0';
	printf("Print text after lseek (fid, 5, SEEK_CUR); : %s End of text.\n", str_buffer);
	
	close(fid);
	
	*/
	
	
	return 0;
}