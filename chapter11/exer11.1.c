#include"apue.h"
#include<pthread.h>

struct foo
{
	int a, b, c ,d;
};

void printfoo(const char *s, const struct foo *fp)
{
	printf(s);
	printf("  struct at 0x%x\n", (unsigned)fp);
	printf("  foo.a = %d\n", fp->a);
	printf("  foo.b = %d\n", fp->b);
	printf("  foo.c = %d\n", fp->c);
	printf("  foo.d = %d\n", fp->d);
}

void *thr_fn1(void *arg)
{
	struct foo *f;

	if((f = malloc(sizeof(struct foo))) == NULL)
	{
		err_quit("malloc error");
	}

	f->a = 1;
	f->b = 2;
	f->c = 3;
	f->d = 4;

	printfoo("thread 1: \n", f);
	pthread_exit((void*)f);
}

void *thr_fn2(void *arg)
{
	printf("thread 2: ID is %ld\n", pthread_self());
	pthread_exit((void*)0);
}

int main()
{
	int err;
	pthread_t tid1, tid2;
	struct foo *fp;
	

	err = pthread_create(&tid1, NULL, thr_fn1, NULL);
	if(err != 0)
			err_quit("can't create thread 1 : %s\n", strerror(err));
	err = pthread_join(tid1, (void*)&fp);
	if(err != 0)
			err_quit("can't join with thread 1: %s\n", strerror(err));
	sleep(1);
	printf("parent starting second thread\n");

	err = pthread_create(&tid2, NULL, thr_fn2, NULL);
	if(err != 0)
			err_quit("can't create thread 2 : %s\n", strerror(err));
	sleep(2);

	printfoo("parent:\n", fp);
	exit(0);
}
