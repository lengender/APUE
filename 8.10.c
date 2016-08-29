#include<sys/wait.h>
#include"apue.h"

int main()
{
	pid_t pid;
	
	if((pid = fork()) < 0)
			err_sys("fork error");
	else if(pid == 0){
		if(execl("/home/nice/unix/bin/testinterp", "testinterp", "myarg1", "my arg2", (char*)0) < 0)
				err_sys("execl error");
	}

	if(waitpid(pid, NULL, 0) < 0)
			err_sys("waitpid error");

	return 0;
}
