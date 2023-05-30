/***********************************************************************************************************
* 6. Создать именованный канал (любым способом). Убедиться, что канал создан. Рассмотреть особенности работы
* с именованным каналом (открыть файл с установленным и не установленным флагом O_NDELAY).
* Использовать его для обмена информацией с процессом, созданным другим пользователем (своим соседом).
***********************************************************************************************************/
#include <stdio.h>
#include <stdlib.h> // int system(const char *s);
#include <sys/types.h> // pid_t 
#include <unistd.h> //  pid_t fork(void); int pipe(int pipefd[2]);
#include <sys/stat.h> // int mkfifo(const char *fifoname, mode_t mode);
#include <fcntl.h> /* Определение констант O_* */
#include <sys/wait.h>
#include <string.h>

int main()
{	
	if(mkfifo("fifo_1", 0660) == -1)
	{
		perror("mkfifo() ");
		exit(-1);
	}
	
	char str2[] = "Simple text writien in child's process, this've read by FIFO(named pipe) in parent's process\n";
	char buffer[128] = {0};
	
	pid_t pid = fork();
	if(pid == 0) //child
	{	
		/*
		int w_fifo = open("fifo_1", O_WRONLY); // | O_NONBLOCK);
		
		if(w_fifo < 0)
		{
			perror("w_fifo = open(); ");
			exit(-1);
		}
		
		write(w_fifo, str2, strlen(str2) + 1);
		close(w_fifo);
		*/
		
		exit(0);
	}
	else if(pid > 0) //parent
	{
		
		int r_fifo = open("fifo_1", O_RDONLY); // | O_NONBLOCK);
		
		if(r_fifo < 0)
		{
			perror("r_fifo = open(); ");
			exit(-1);
		}
		wait(NULL);
		read(r_fifo, buffer, sizeof(buffer));
		printf("%s", buffer);
		close(r_fifo);
		
		exit(0);
	}
	else //error fork()
	{
		perror("After fork() ");
		exit(-1);
	}

}
