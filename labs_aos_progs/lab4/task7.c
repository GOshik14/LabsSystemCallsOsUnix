/***********************************************************************************************************
* 7. Создать два параллельных процесса, в каждом из которых осуществляется работа с одним и тем же файлом.
* Каждый процесс открывает файл (имя файла передается через список аргументов командной строки).
* Один процесс пишет в файл, другой - читает из него. Что произойдет без включения блокировок?
***********************************************************************************************************/

#include <stdlib.h> // int system(const char *s);
#include <stdio.h> // perror(const char *s);
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <unistd.h> // pid_t fork(void); int close (int fd); off_t lseek(int fildes, off_t offset, int whence);
//ssize_t read (int fd, void * buffer, size_t count);
//ssize_t write (int fd, const void * buffer, size_t count);
//unsigned int sleep(unsigned int seconds);

// env > env.txt //create file with environment info =)

#define BUFF_SIZE 10

int file_copy(const int fd_src, const int fd_dst);

int main(int argc, char *argv[])
{
	if(argc != 2)
	{
		printf("Bad comand's line arguments! Try again.\n");
		return -1;
	}
	
	int fd_common = open(argv[1], O_RDWR);
	
	pid_t pid = fork();
	
	if(pid == 0) //child ps
	{
		file_copy(fd_common, 1);
		return 0;
	}
	else if( pid > 0) //parent ps
	{
		file_copy(0, fd_common);
		//wait(&child_status);
		//printf("Parent: Child process pid = %d returned : %d\n", pid, WEXITSTATUS(child_status));
		//printf("Parent print!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n");
		return 0;
	}
	else
	{
		printf("Cann't fork main process!\n");
		return -2;
	}

}

int file_copy(const int fd_src, const int fd_dst)
{
	char buff[BUFF_SIZE] = {0};
	int read_bytes = 0;
	int written_bytes_step = 0;
	int written_bytes= 0;
	
	//copy from start src_file to start dst_file !!!
	lseek (fd_src, 0, SEEK_SET);
	lseek (fd_dst, 0, SEEK_SET);
	
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


