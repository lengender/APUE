/*************************************************************************
	> File Name: 15.11.c
	> Author: 
	> Mail: 
	> Created Time: 2016年09月04日 星期日 10时19分26秒
 ************************************************************************/

#include"apue.h"
#include<sys/shm.h>

#define ARRAY_SIZE 40000
#define MALLOC_SIZE 100000
#define SHM_SIZE    100000
#define SHM_MODE    0600

char array[ARRAY_SIZE];

int main()
{
    int shmid;
    char *ptr, *shmptr;

    printf("array[] from %lx to %lx\n", (unsigned long)&array[0],
            (unsigned long)&array[ARRAY_SIZE]);
    
    printf("stack around: %lx\n", (unsigned long) &shmid);

    if((ptr = malloc(MALLOC_SIZE)) == NULL)
        err_sys("malloc error");
    printf("malloced from %lx to %lx\n", (unsigned long)ptr,
          (unsigned long)ptr + MALLOC_SIZE);

    if((shmid = shmget(IPC_PRIVATE, SHM_SIZE, SHM_MODE)) < 0)
        err_sys("shmget error");
    if((shmptr = shmat(shmid, 0, 0)) == (void*)-1)
        err_sys("shmat error");
    printf("shared memeory attached from %lx to %lx\n", (unsigned long)shmptr,
            (unsigned long)shmptr + SHM_SIZE);

    if(shmctl(shmid, IPC_RMID, 0) < 0)
        err_sys("shmctl error");

    exit(0);
}

