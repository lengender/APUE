CC = gcc
inc = /home/nice/unix/include/apue.h 
err = /home/nice/unix/include/error.c 
OBJ = signal_intr.o 14.2.o exec14.1.o

%.o : %.c $(err)
	$(CC) -c -w -o $@ $< 

a.out : $(OBJ) $(err)
	$(CC) -w -I $(inc) -o a.out $^ 

clean:
	rm -rf *.o
