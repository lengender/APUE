//#include<stdio.h>
//#include<stdlib.h>
//#include<string.h>
//#include<sys/stat.h>
//#include<unistd.h>
//#include<signal.h>
#include<fcntl.h>	
#include"./include/apue.h"
int main()
{
	pid_t pid;
	int i = 0;
	int fd;

	char *child = "child write\n";
	char *parent = "parent write\n";
	FILE *fp;
	fp = fopen("temp", "a");
	if(!fp)
			perror("fopen error");

	fd = fileno(fp);
	fprintf(fp, "%d\n", i);
    fflush(fp);

	TELL_WAIT();

	if((pid = fork()) < 0)
		perror("fork error");
	else if(pid == 0)
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


	fclose(fp);
	return (0);
}
