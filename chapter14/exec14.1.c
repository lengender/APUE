/*************************************************************************
	> File Name: exec14.1.c
	> Author: 
	> Mail: 
	> Created Time: 2016年09月02日 星期五 17时42分41秒
 ************************************************************************/

#include"../include/apue.h"
#include<fcntl.h>
#include<errno.h>

void sigint(int signo)
{

}

int main()
{
    pid_t pid1, pid2, pid3;
    int fd;

    setbuf(stdout, NULL);  //关闭缓冲
    signal_intr(SIGINT, sigint);

    if((fd = open("lockfile", O_RDWR | O_CREAT, 0666)) < 0)
        err_sys("can't open/creat lockfile");

    if((pid1 = fork()) < 0)
        err_sys("fork failed");
    else if(pid1 == 0){
        if(lock_reg(fd, F_SETLK, F_RDLCK, 0, SEEK_SET, 0) < 0)
            err_sys("child1: can't read-lock file\n");

        printf("child1: obtained read lock in file\n");
        pause();
        printf("cilld1: exit after pause\n");
        exit(0);
    }else sleep(2);

    if((pid2 = fork()) < 0)
        err_sys("fork failed");
    else if(pid2 == 0){
        if(lock_reg(fd, F_SETLK, F_RDLCK, 0, SEEK_SET, 0) < 0)
            err_sys("child2: can't read-lock file");
        printf("child2: obtained read lock on file\n");
        pause();
        printf("child2: exit after pause\n");
        exit(0);
    }else sleep(2);

    if((pid3 = fork()) < 0)
        err_sys("fork failed");
    else if(pid3 == 0){
        if(lock_reg(fd, F_SETLK, F_WRLCK, 0, SEEK_SET, 0) < 0)
            printf("child3: can't set write lock: %s\n", strerror(errno));

        printf("child3 about to block in write-locking...\n");
        if(lock_reg(fd, F_SETLKW, F_WRLCK, 0, SEEK_SET, 0) < 0)
            err_sys("child3：　can't write-lock file");
        printf("child3: returned and got write lock???\n");
        pause();
        printf("child3: exit after pause\n");
        exit(0);
    }else sleep(2);

    if(lock_reg(fd, F_SETLK, F_RDLCK, 0, SEEK_SET, 0) < 0)
        printf("parent: can't set read lock: %s\n", strerror(errno));
    else
        printf("parent: obtained additional read lock while "
              "write lock is pending\n");

    printf("killing child1..\n");
    kill(pid1, SIGINT);
    printf("kill child2..\n");
    kill(pid2, SIGINT);
    printf("kill child3..\n");
    kill(pid3, SIGINT);
    exit(0);
}
