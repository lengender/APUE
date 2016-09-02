/*************************************************************************
	> File Name: 14.10.c
	> Author: 
	> Mail: 
	> Created Time: 2016年09月01日 星期四 22时31分14秒
 ************************************************************************/

#include"apue.h"
#include<stropts.h>

#define BUFFSIZE 4096

int main()
{
    int n, flag;
    char ctlbuf[BUFFSIZE], datbuf[BUFFSIZE];
    struct strbuf ctl, dat;

    ctl.buf = ctl.buf;
    ctl.maxlen = BUFFSIZE;
    dat.buf = datbuf;
    dat.maxlen = BUFFSIZE;

    for(; ;)
    {
        flag = 0;
        if((n = getmsg(STDIN_FILENO, &ctl, &dat, &flag)) < 0)
            err_sys("getmsg error");

        fprintf(stderr, "flag = %d, ctl.len = %d, dat.len = %d\n",
               flag, ctl.len, dat.len);
        if(dat.len == 0)
            exit(0);
        else if(dat.len > 0)
            if(write(STDOUT_FILENO, dat.buf, dat.len) != dat.len)
                err_sys("write error");
    }

    return 0;
}
