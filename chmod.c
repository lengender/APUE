#include"apue.h"

int main()
{
	struct stat statbuf;

	//turn on set-grout-ID and turn off grout-execute
	if(stat("foo", &statbuf) < 0)
		err_sys("stat error for foo");
	if(chmod("foo", (statbuf.st_mode & ~S_IXGRP) | S_ISGID) < 0)
		err_sys("chmod error for foo");

	//set absolute mode to 'rw-r--r--'
	if(chmod("bar", S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH) < 0)
		err_sys("chmod error for bar");

	return 0;
}
