#include"apue.h"

int glob = 6;

int main()
{
	int var;
	pid_t pid;

	var = 88;
	printf("before fork.\n");

	if((pid = vfork()) < 0)
	{
		err_sys("fork error");
	}else if(pid == 0){
		glob++;
		var++;
		fclose(stdout);
		exit(0);
	}
 
	int i;
	char buf[100];
	i =	printf("pid = %d, glob = %d, var = %d\n", getpid(), glob, var);
	sprintf(buf, "%d\n", i);
	write(STDOUT_FILENO, buf, strlen(buf));
	return 0;
}
