/*************************************************************************
	> File Name: 15.3.c
	> Author: 
	> Mail: 
	> Created Time: 2016年09月03日 星期六 10时53分31秒
 ************************************************************************/

#include"../include/apue.h"

static int pfd1[2], pfd2[2];

void TELL_WAIT()
{
    if(pipe(pfd1) < 0 || pipe(pfd2) < 0)
        err_sys("pipe error");
}

void TELL_PARENT(pid_t pid)
{
    if(write(pfd2[1], "c", 1) != 1)
        err_sys("write parent error");
}

void WAIT_PARENT()
{
    char c;
    
    if(read(pfd1[0], &c, 1) != 1)
        err_sys("read error");

    if(c != 'p')
        err_quit("WAIT_PARENT: incorrect data");
}

void TELL_CHILD(pid_t pid)
{
    if(write(pfd1[1], "p", 1) != 1)
        err_sys("write child error");
}

void WAIT_CHILD()
{
    char c;

    if(read(pfd2[0], &c, 1) != 1)
        err_sys("read error");

    if(c != 'c')
    err_quit("WAIT_CHILD: incorrect data");
}
