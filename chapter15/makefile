CC = gcc
inc = /home/nice/unix/include/apue.h
err = /home/nice/unix/include/error.c
obj = 15.3.o 15.12.o

%.o : %.c $(err)
	$(CC) -w -c -o $@ $<

a.out: $(obj)
	$(CC) -w -o a.out $^ $(err) -I $(inc)


clean:
	rm -rf *.o
