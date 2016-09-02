/*************************************************************************
	> File Name: 14.5.c
	> Author: 
	> Mail: 
	> Created Time: 2016年09月01日 星期四 11时32分35秒
 ************************************************************************/

#include<unistd.h>
#include<fcntl.h>

int lockfile(int fd)
{
    struct flock fl;

    fl.l_type = F_WRLCK;
    fl.l_start = 0;
    fl.l_whence = SEEK_SET;
    fl.l_len = 0;
    return (fcntl(fd, F_SETLK, &fl));

}
