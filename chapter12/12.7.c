#include"apue.h"
#include<pthread.h>

pthread_mutex_t lock1 = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t lock2 = PTHREAD_MUTEX_INITIALIZER;

void prepare()
{
	printf("prepareing locks..\n");
	pthread_mutex_lock(&lock1);
	pthread_mutex_lock(&lock2);
}

void parent()
{
	printf("parent unlocking..\n");
	pthread_mutex_unlock(&lock1);
	pthread_mutex_unlock(&lock2);
}

void child()
{
	printf("child unlocking..\n");
	pthread_mutex_unlock(&lock1);
	pthread_mutex_unlock(&lock2);
}

void *thr_fn(void *arg)
{
	printf("thread started..\n");
	pause();
	return 0;
}

int main()
{
	int err;
	pid_t pid;
	pthread_t tid;

#if defined(BSD) || defined(MACOS)
	printf("pthead_atfork is unsupported\n");
#else
	if((err = pthread_atfork(prepare, parent, child)) != 0)
			err_exit(err, "can't install fork handlers");
	err = pthread_create(&tid, NULL, thr_fn, NULL);
	if(err != 0)
			err_exit(err, " can't create thread");
	sleep(2);

	printf("parent about to fork ..\n");
	if((pid = fork()) < 0)
			err_quit("fork failed");
	else if(pid == 0)
			printf("child returned from fork\n");
	else 
			printf("parent returned from fork\n");
#endif
	exit(0);
}
