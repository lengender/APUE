/*************************************************************************
	> File Name: signal_intr.c
	> Author: 
	> Mail: 
	> Created Time: 2016年09月02日 星期五 18时04分30秒
 ************************************************************************/

#include"../include/apue.h"

Sigfunc *signal_intr(int signo, Sigfunc *func)
{
    struct sigaction act, oact;

    act.sa_handler = func;
    sigemptyset(&act.sa_mask);
    act.sa_flags = 0;
    
#ifdef SA_INTERRUPT
    act.sa_flags |= SA_INTERRUPT;
#endif
    if(sigaction(signo, &act, &oact) < 0)
        return SIG_ERR;
    return oact.sa_handler;
}
