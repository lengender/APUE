#include"apue.h"
#include<setjmp.h>
#include<signal.h>
#include<unistd.h>

static jmp_buf env_alarm;

static void sig_alarm(int signo)
{
	longjmp(env_alarm, 1);
}

unsigned int sleep2(unsigned int nsecs)
{
	if(signal(SIGALRM, sig_alarm) == SIG_ERR)
			return nsecs;

	if(setjmp(env_alarm) == 0)
	{
			alarm(nsecs);
			pause();
	}
	return (alarm(0));
}

static void sig_int(int signo)
{
	int i, j;
	volatile int k;

	printf("\nsig_int starting \n");
	for(i = 0; i < 300000; ++i)
	{
		for(j = 0; j < 4000; ++j)
				k += i * j;
	}
	printf("sig_int finished\n");
}

int main()
{
	unsigned int unslept;
	if(signal(SIGINT, sig_int) == SIG_ERR)
			err_sys("signal(SIGINT) error");

	unslept = sleep2(5);
	printf("sleep2 returned: %u\n", unslept);
	return 0;
}
