#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>
#include"apue.h"
char buf1[] = "abcdefghij";
char buf2[] = "ABCDEFGHIJ";

int main(void)
{
	int fd;

	if((fd = creat("file.hole", FILE_MODE)) < 0)
	   printf("creat error");
	
	if(write(fd, buf1, 10) != 10)
	   printf("buf1 write error\n");

	if(lseek(fd, 16384, SEEK_SET) == -1)
		printf("lseek error\n");
	
	if(write(fd, buf2, 10) != 10)
		printf("buf2 write error\n");

	return 0;
}
