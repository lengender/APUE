#include"apue.h"
#include<pwd.h>

static void my_alarm(int signo)
{
	struct passwd *rootptr;

	printf("int signal handler\n");
	if((rootptr = getpwnam("root")) == NULL)
			err_sys("getpwnam(root) error");
	alarm(1);
}

int main()
{
	struct  passwd *ptr;

	signal(SIGALRM, my_alarm);
	alarm(1);

	for(; ;)
	{
		if((ptr = getpwnam("nice")) == NULL)
				err_sys("getpwnam(nice) error");

		if(strcmp(ptr->pw_name, "nice") != 0)
				printf("return value corrupted , pw_name: %s\n", ptr->pw_name);
	}

	return 0;
}
