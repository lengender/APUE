#include"apue.h"
#include<syslog.h>
#include<errno.h>

extern int lockfile(int file);
extern int already_running(void);

void reread()
{

}

void sigterm(int signo)
{
	syslog(LOG_INFO, "got SIGTERM ; exiting");
	exit(0);
}

void sighup(int signo)
{
	siglog(LOG_INFO, "Re-reading configuration file");
	reread();
}

int main(int argc, char *argv[])
{
	char *cmd;
	struct sigaction sa;

	if((cmd = strrchr(argv[0], '/')) == NULL)
			cmd = argv[0];
	else cmd++;

	daemonize(cmd);

	if(alredy_running())
	{
		syslog(LOG_ERR, "daemon already running");
		exit(1);
	}

	sa.sa_handler = sigterm;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	if(sigaction(SIGHUP, &sa, NULL) < 0)
	{
		syslog(LOG_ERR, "can't catch SIGHUP: %s", strerror(errno));
		exit(1);
	}

	exit(0);
}

