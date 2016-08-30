#include"apue.h"


int main()
{
	pid_t pid;


	if((pid = fork()) < 0)
	{
		err_sys("fork error");
	}else if(pid == 0){
		if((pid = fork()) < 0)
				err_sys("fork error");
		else if(pid > 0)
		{
				printf("1 first child id: %d\n", getpid());
				exit(0);
		}
		
		sleep(10);
		printf("second child, parent pid = %d\n", getppid());
		exit(0);
	}

	if(waitpid(pid, NULL, 0) != pid)
			err_sys("waitpid error");

	printf("first child id = %d, %d\n", pid, getpid());
	return 0;
}
