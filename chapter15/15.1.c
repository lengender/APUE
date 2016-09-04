/*************************************************************************
	> File Name: 15.1.c
	> Author: 
	> Mail: 
	> Created Time: 2016年09月03日 星期六 10时29分09秒
 ************************************************************************/

#include"apue.h"

int main()
{
    int n;
    int fd[2];
    pid_t pid;
    char line[MAXLINE];

    if(pipe(fd) < 0)
        err_sys("pipe error");

    if((pid = fork()) < 0)
        err_sys("fork error");
    else if(pid > 0){
        close(fd[0]);
        write(fd[1], "hello world\n", 12);
    }else{
        close(fd[1]);
        n = read(fd[0], line, MAXLINE);
        write(STDOUT_FILENO, line, n);
    }

    return 0;
}
