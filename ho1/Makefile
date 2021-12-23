CC=gcc
CFLAGS=-I

%.o: %.c
	$(CC) -c -o $@ $< # $(CFLAGS)

hellomake: helloworld.o
	$(CC) -o hellomake helloworld.o
