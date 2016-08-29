#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/stat.h>
#include<signal.h>

static volatile sig_atomic_t sigflag;
static sigset_t newmask, oldmask, zeromask;

static void sig_usr(int signo)
{
	sigflag = 1;
}

void TELL_WAIT()
{
	if(signal(SIGUSR1, sig_usr) == SIG_ERR)
	{
		perror("signal(SIGUSR1) error");
		exit(1);
	}

	if(signal(SIGUSR2, sig_usr) == SIG_ERR)
	{
		perror("signal(SIGUSR2) error");
		exit(1);
	}

	sigemptyset(&zeromask);
	sigemptyset(&newmask);
	sigaddset(&newmask, SIGUSR1);
	sigaddset(&newmask, SIGUSR2);

	if(sigprocmask(SIG_BLOCK, &newmask, &oldmask) < 0)
	{
		perror("SIG_BLOCK error");
		exit(1);
	}
}

void TELL_PARENT(pid_t pid)
{
	kill(pid, SIGUSR2);
}

void WAIT_PARENT()
{
	while(sigflag == 0)
			sigsuspend(&zeromask);
	sigflag = 0;

	if(sigprocmask(SIG_SETMASK, &oldmask, NULL) < 0)
	{
		perror("SIG_SETMASK error");
		exit(1);
	}
}

void TELL_CHILD(pid_t pid)
{
	kill(pid, SIGUSR1);
}

void WAIT_CHILD()
{
	while(sigflag == 0)
			sigsuspend(&zeromask);
	sigflag = 0;

	if(sigprocmask(SIG_SETMASK, &oldmask, NULL) < 0)
	{
		perror("SIG_SETMASK error");
		exit(1);
	}
}

