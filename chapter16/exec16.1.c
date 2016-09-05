/*************************************************************************
	> File Name: exec16.1.c
	> Author: 
	> Mail: 
	> Created Time: 2016年09月05日 星期一 17时15分24秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<inttypes.h>

int main()
{
    uint32_t i;
    unsigned char *cp;
    i = 0x04030201;
    cp = (unsigned char*)&i;

    if(*cp == 1)
        printf("little-endian\n");
    else if(*cp == 4)
        printf("big-endian\n");
    else 
        printf("who knows\n");

    exit(0);
}
