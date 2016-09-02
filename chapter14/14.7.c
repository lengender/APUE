/*************************************************************************
	> File Name: 14.7.c
	> Author: 
	> Mail: 
	> Created Time: 2016年09月01日 星期四 21时56分09秒
 ************************************************************************/

#include<stropts.h>
#include<unistd.h>

int isastream(int fd)
{
    return (ioctl(fd, I_CANPUT, 0) != -1);
}
