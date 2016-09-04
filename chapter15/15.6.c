/*************************************************************************
	> File Name: 15.6.c
	> Author: 
	> Mail: 
	> Created Time: 2016年09月03日 星期六 11时46分14秒
 ************************************************************************/

#include"apue.h"
#include<ctype.h>

int main()
{
    int c;
    
    while((c = getchar()) != EOF)
    {
        if(isupper(c))
            c = tolower(c);

        if(putchar(c) == EOF)
            err_sys("output error");

        if(c == '\n')
            fflush(stdout);
    }

    return 0;
}
