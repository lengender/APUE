#include"./include/apue.h"
#include<setjmp.h>
#include<time.h>

static sigjmp_buf jmpbuf;
static volatile sig_atomic_t canjump;

static void sig_usr1(int signo)
{
	time_t starttime;

	sigset_t newmask, oldmask;
	sigemptyset(&newmask);
	sigaddset(&newmask, SIGUSR1);
	if(sigprocmask(SIG_BLOCK, &newmask, &oldmask) < 0)
			err_sys("sigprocmask error");
	pr_mask("in sig_alrm: ");
	if(canjump == 0)
			return;

	pr_mask("starting sig_usr1: ");

	alarm(3);

	starttime = time(NULL);
	for(; ;)
	{
		if(time(NULL) > starttime + 5)
				break;
	}
		
	pr_mask("finishing sig_usr1 : ");
    
	canjump = 0;

	if(sigprocmask(SIG_SETMASK, &oldmask, NULL) < 0)
			err_sys("sigprocmask(oldmask) error");
	siglongjmp(jmpbuf, 1);
}

static void sig_alrm(int signo)
{
		sigset_t newmask, oldmask;
		sigemptyset(&newmask);
		sigaddset(&newmask, SIGALRM);
		if(sigprocmask(SIG_BLOCK, &newmask, &oldmask) < 0)
				err_sys("sigprocmask error");
		pr_mask("in sig_alrm: ");
		if(sigprocmask(SIG_SETMASK, &oldmask, NULL) < 0)
				err_sys("sigprocmask(oldmask) error");
}

int main()
{
	if(signal(SIGUSR1, sig_usr1) == SIG_ERR)
			err_sys("signal(SIGUSR1) error");
	if(signal(SIGALRM, sig_alrm) == SIG_ERR)
			err_sys("signal(SIGALRM) error");
	pr_mask("starting main: ");

	if(sigsetjmp(jmpbuf, 1))
	{
		pr_mask("ending main: ");
		exit(0);
	}

	canjump = 1;
	for(; ;)
	     pause();
}
