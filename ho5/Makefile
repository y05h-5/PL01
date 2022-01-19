CC=gcc
PROGRAM = ho5
D_OUT = outputs/
B = build/
OBJ = $(B)ho5.o $(B)max.o $(B)file_operation.o 
HEADER = defines.h file_operation.h max.h
LIBM = -lm

all: $(PROGRAM).exe $(D_OUT)

$(PROGRAM).exe: $(OBJ)
	$(CC) $^ -o $@ $(LIBM)

$(B)%.o: %.c $(HEADER) $(B)
	$(CC) -c $< -o $@

$(B):
	mkdir $(B)

$(D_OUT):
	mkdir $(D_OUT)

clean:
	rm -f *.exe *.gch outputs/* build/*
  
run: $(PROGRAM).exe
	./$(PROGRAM).exe

.PHONY: clean run
