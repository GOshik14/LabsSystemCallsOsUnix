/***********************************************************************************************************
* 8. Добавить в один из процессов использование слабой блокировки. Что 
* произойдет?
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
	
	int fd_common = open(argv[1], O_RDONLY);
	
	pid_t pid = fork();
	
	if(pid == 0) //child ps
	{
		int fd_child = open("child.txt", O_CREAT | O_RDWR, 0666);
		file_copy(fd_common, fd_child);
		printf("Child print!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n");
	  
	    /*
		struct flock lock = {0};
		
		if(fcntl(1, F_GETLK, &lock) == -1)
		{
			perror("fcntl(fd_src, F_GETLK, &lock)");
			exit(1);
		}
		
		lock.l_start = 0;
		lock.l_len = 0;
		lock.l_whence = SEEK_SET;
		lock.l_pid = getpid();
		
		lock.l_type = F_WRLCK;
		fcntl(1, F_SETLKW, &lock);
		*/
		file_copy(fd_child, 1);	
		/*
		lock.l_type = F_UNLCK;
		fcntl(1, F_SETLK, &lock);
		*/
		
		close(fd_child);
		return 0;
	}
	else if( pid > 0) //parent ps
	{
		int fd_parent = open("parent.txt", O_CREAT | O_RDWR, 0666);
		
		file_copy(fd_common, fd_parent);
		
		int child_status;
		//wait(&child_status);
		printf("Parent: Child process pid = %d returned : %d\n", pid, WEXITSTATUS(child_status));
		printf("Parent print!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n");
		file_copy(fd_parent, 1);
		close(fd_parent);
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


