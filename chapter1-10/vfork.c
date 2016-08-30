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
		_exit(0);
	}

	printf("pid = %d, glob = %d, var = %d\n", getpid(), glob, var);
	return 0;
}
