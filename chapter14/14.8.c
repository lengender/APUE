/*************************************************************************
	> File Name: 14.8.c
	> Author: 
	> Mail: 
	> Created Time: 2016年09月01日 星期四 21时57分24秒
 ************************************************************************/

#include<fcntl.h>
#include"../include/apue.h"

int main(int argc, char *argv[])
{
    int i, fd;

    for(i = 1; i < argc; ++i)
    {
        if((fd = open(argv[i], O_RDONLY)) < 0)
        {
            err_ret("%s: can't open", argv[i]);
            continue;
        }
    
    
        if(isastream(fd) == 0)
            err_ret("%s: not a stream", argv[i]);
        else 
            err_msg("%s: stream device", argv[i]);
    }
    return 0;
}
