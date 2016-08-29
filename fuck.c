#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/stat.h>
#include<signal.h>


int main()
{
	pid_t pid;
	FILE *fp;
	int fd;
	int i = 0;
	char *child = "in child\n";
	char *parent = "int parent\n";

	fp = fopen("temp", "a");
	if(fp == NULL)
	{
		perror("fopen error");
		exit(1);
	}

	fd  = fileno(fp);
	fprintf(fp, "%d\n", i);
	fflush(fp);

	TELL_WAIT();

	if((pid = fork()) < 0)
	{
		perror("fork error");
		exit(1);
	}else if(pid == 0)
	{
		while(i < 10)
		{
			WAIT_PARENT();
			i += 2;
			fprintf(fp, "%d\t", i);
			fflush(fp);

			write(fd, child, strlen(child));
			TELL_PARENT(getppid());
		}
	}else{
		i++;
		while(i < 10)
		{
			fprintf(fp, "%d\t", i);
			fflush(fp);
			i += 2;
			write(fd, parent, strlen(parent));
			TELL_CHILD(pid);
			WAIT_CHILD();
		}
	}
	return 0;
}
