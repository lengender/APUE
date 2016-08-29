#include"apue.h"

void mysetbuf(FILE *fp, char *buf);

int main()
{
	char buf[BUFSIZ];
	FILE *fp;

	if((fp = fopen("1", "w")))
	{
		mysetbuf(fp, buf);
		mysetbuf(stdin, NULL);
		mysetbuf(stdout, buf);
		mysetbuf(fp, NULL);
	}
	fclose(fp);

	return 0;
}

void mysetbuf(FILE *fp, char *buf)
{
	if(buf == NULL)
	{
		if(setvbuf(fp, buf, _IONBF, BUFSIZ) != 0)
		{
			err_sys("setvbuf error");
			exit(-1);
		}
		printf("no buf\n");
	}else if(fp == stderr){
		if(setvbuf(fp, buf, _IONBF, BUFSIZ) != 0)
		{
			err_sys("setvbuf error");
			exit(-1);
		}
		printf("no buf\n");
	}else if(fp == stdin || fp == stdout){
		if(setvbuf(fp, buf, _IOLBF, BUFSIZ) != 0)
		{
			err_sys("setvbuf error");
			exit(-1);
		}
		printf("line buf\n");
	}else {
		if(setvbuf(fp, buf, _IOFBF, BUFSIZ) != 0)
		{
			err_sys("setvbuf error");
			exit(-1);
		}
		printf("full buf\n");
	}
}
