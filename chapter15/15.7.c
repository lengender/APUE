/*************************************************************************
	> File Name: 15.7.c
	> Author: 
	> Mail: 
	> Created Time: 2016年09月03日 星期六 11时49分44秒
 ************************************************************************/

#include"apue.h"
#include<ctype.h>

int main()
{
    char line[MAXLINE];
    FILE *fpin;

    if((fpin = popen("./myuclc", "r")) == NULL)
        err_sys("popen error");

    for(; ;)
    {
        fputs("prompt> : " , stdout);
        fflush(stdout);
        if(fgets(line, MAXLINE, fpin) == NULL)
            break;

        if(fputs(line, stdout) == EOF)
            err_sys("fputs error to pipe");
    }

    if(pclose(fpin) == -1)
        err_sys("pclose error");
    putchar("\n");

    exit(0);
}
