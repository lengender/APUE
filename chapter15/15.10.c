/*************************************************************************
	> File Name: 15.10.c
	> Author: 
	> Mail: 
	> Created Time: 2016年09月03日 星期六 13时02分28秒
 ************************************************************************/

#include"apue.h"

int main()
{
    int int1, int2;
    char line[MAXLINE];

    if(setvbuf(stdout, NULL, _IOLBF, 0) != 0)
        err_sys("setvbuf error");
    if(setvbuf(stdin, NULL, _IOLBF, 0) != 0)
        err_sys("setvbuf error");

    while(fgets(line, MAXLINE, stdin) != NULL)
    {
        if(sscanf(line, "%d%d", &int1, &int2) == 2)
        {
            if(printf("%d\n", int1 + int2) == EOF)
                err_sys("printf error");
        }else {
            if(printf("invalid args\n") == EOF)
                err_sys("printf error");
        }
    }

    return 0;
}
