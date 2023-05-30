#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h> // int stat(const char *file_name, struct stat *buf);

#include <stdio.h> //int sprintf(char *s, const char *format,...);
#include <stdlib.h>

/*
struct stat {
    dev_t         st_dev;      // устройство
    ino_t         st_ino;      // inode
    mode_t        st_mode;     // режим доступа
    nlink_t       st_nlink;    // количество жестких ссылок
    uid_t         st_uid;      // идентификатор пользователя-владельца
    gid_t         st_gid;      // идентификатор группы-владельца
    dev_t         st_rdev;     // тип устройства
                               // (если это устройство)
    off_t         st_size;     // общий размер в байтах
    blksize_t     st_blksize;  // размер блока ввода-вывода
                               // в файловой системе
    blkcnt_t      st_blocks;   // количество выделенных блоков
    time_t        st_atime;    // время последнего доступа
    time_t        st_mtime;    // время последней модификации
    time_t        st_ctime;    // время последнего изменения
};
*/

int main(int argc, char *argv[]) //argv[1] - file's name, argv[2] - file's permissions -> int(0444),
{	
	if(argc != 2)
	{
		printf("Too few or many command's parameter!\n");
		return -1;
	}
	
	struct stat *st_stat = (struct stat *)malloc(sizeof(struct stat));
	if(stat(argv[1], st_stat) == -1)
	{
		perror("Error stat() ");
		return -1;
	}
	
	//printf("st_stat.st_dev = %s\n", st_stat->st_dev);
	printf("st_stat.st_ino = %u\n", st_stat->st_ino);
	printf("st_stat.st_mode = %o\n", st_stat->st_mode);
	printf("st_stat.st_nlink = %d\n", st_stat->st_nlink);
	printf("st_stat.st_uid = %u\n", st_stat->st_uid);
	printf("st_stat.st_gid = %u\n", st_stat->st_gid);
	//printf("st_stat.st_rdev = %s\n", st_stat->st_rdev);
	printf("st_stat.st_size = %u\n", st_stat->st_size);
	printf("st_stat.st_blksize = %u\n", st_stat->st_blksize);
	printf("st_stat.st_blocks = %u\n", st_stat->st_blocks);
	printf("st_stat.st_atime = %u\n", st_stat->st_atime);
	printf("st_stat.st_mtime; = %u\n", st_stat->st_mtime);
	printf("st_stat.st_ctime = %u\n", st_stat->st_ctime);

	char command_line[32];
	sprintf(command_line, "stat %s", argv[1] );
	
	system(command_line);
	
	return 0;
}