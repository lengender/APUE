#include<unistd.h>
#include<fcntl.h>
#include<string.h>
#include<sys/types.h>
#include<sys/stat.h>


#define OPEN_MAX 256
int my_dup2(int fd, int newfd);

int main(int argc, char *argv[])
{
	int newdup = 3;
	const char* filename = "newfile.txt";
	int fd = open(filename, O_RDWR);
	int newfd = my_dup2(fd, newdup);

	if(write(newfd, "Test new fd.", strlen("Test new fd.")) < 0)
	{
		printf("Use new write file failed\n");
		exit(2);
	}else
		printf("Write syccessfully\n");

	return 0;
}

int my_dup2(int fd, int newfd)
{
	int temp;
	int count = 0;
	int fdarray[newfd];

	if(newfd < 0 || newfd > OPEN_MAX)
	{
		printf("newfd error.\n");
		exit(0);
	}

	if((fdarray[count] = dup(fd)) == -1)   // 判断原文件描述符是否有效	
	{
		printf("fd is invalid.\n");
		exit(0);
	}else{
		close(fdarray[count]);
	}

	if(fd == newfd)
		return fd;

	close(newfd);

	for(count = 0; count <= newfd; ++count)
	{
		fdarray[count] = dup(fd);    //返回当前可用的最小文件描述符
		if(fdarray[count] == -1)
		{
			printf("dup() error\n");
			exit(0);
		}
		else if(fdarray[count] == newfd)
			break;
	}

	for(count = 0; count <= newfd; ++count)
	{
		if(fdarray[count] == newfd)
			return fdarray[count];
		else close(fdarray[count]);
	}
}







