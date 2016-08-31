CC = gcc
inc = /home/nice/unix/include/apue.h
cflg = /home/nice/unix/include/error.c
obj = 12.1.o 12.2.o

%.o : %.c %(cflg)
	$(CC) -c -w -o $@ $< -I $(inc) -lpthread

a.out : $(obj) $(cflg)
	$(CC) -w -o a.out $^ -lpthread

clean:
	rm -rf *.o
