/*************************************************************************
	> File Name: 16.2.c
	> Author: 
	> Mail: 
	> Created Time: 2016年09月05日 星期一 09时16分11秒
 ************************************************************************/

#include"../include/apue.h"
#include<sys/socket.h>

#define MAXSLEEP 128

int connect_retry(int sockfd, const struct sockaddr *addr, socklen_t alen)
{
    int nsec;

    for(nsec = 1; nsec <= MAXSLEEP; nsec <<= 1)
    {
        if(connect(sockfd, addr, alen) == 0)
        {
            //connect accepted;
            return 0;
        }

        if(nsec <= MAXSLEEP / 2)
            sleep(nsec);
    }
    return -1;
}
