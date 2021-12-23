CC=gcc
PROGRAM = interactive

$(PROGRAM): interactive.o
	$(CC) -o interactive interactive.o

%o: %c
	$(CC) -c -o interactive.o

clean:
	rm -f $(PROGRAM) *.o *.exe