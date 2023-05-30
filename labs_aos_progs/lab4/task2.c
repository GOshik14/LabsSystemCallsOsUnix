/***********************************************************************************************************
* 2. Модифицировать программу п. 1 таким образом, чтобы родительский процесс читал из канала в цикле,
* пока не встретится конец файла (порожденный процесс может записывать в канал информацию,
* читаемую им из стандартного входного потока).
* Как избежать бесконечного ожидания родительским процессом чтения из пустого канала?
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
	int pipefd[2];
	if(pipe(pipefd) == -1)
	{
		perror("pipe() ");
		exit(-1);
	}

#ifdef task1	
	if(mkfifo("fifo_1", 0660) == -1)
	{
		perror("mkfifo() ");
		exit(-1);
	}

#endif

	
	char str[] = "Simple text writien in parent's process, this've read by pipe in child's process\n";
	char str2[] = "Simple text writien in child's process, this've read by FIFO(named pipe) in parent's process\n";
	char buffer[128] = {0};
	
	pid_t pid = fork();
	if(pid == 0) //child
	{
		close(pipefd[0]); /* Close unused read end */
		write(pipefd[1], str, strlen(str) + 1);
		close(pipefd[1]);
		
#ifdef task1
		int w_fifo = open("fifo_1", O_WRONLY);
		if(w_fifo < 0)
		{
			perror("w_fifo = open(); ");
			exit(-1);
		}

		write(w_fifo, str2, strlen(str2) + 1);
		close(w_fifo);
#endif		
		exit(0);
	}
	else if(pid > 0) //parent
	{
		sleep(1);
		
		close(pipefd[1]); /* Close unused write end */
		
		int c_ch = 0;
		while ( (c_ch = read(pipefd[0], buffer, 8)) > 0) 
			write(1, buffer, c_ch);
				
		close(pipefd[0]);
		
#ifdef task1		
		int r_fifo = open("fifo_1", O_RDONLY);
		if(r_fifo < 0)
		{
			perror("r_fifo = open(); ");
			exit(-1);
		}
		wait(NULL);
		read(r_fifo, buffer, sizeof(buffer));
		printf("%s", buffer);
		
		system("rm -f fifo_1");

#endif

		exit(0);
	}
	else //error fork()
	{
		perror("After fork() ");
		exit(-1);
	}

}
