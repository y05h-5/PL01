CC = gcc
PROGRAM = ho5
D_OUT = outputs/
B = build/
TEST = test.sh
OBJ = $(B)ho5.o $(B)max.o $(B)file_operation.o 
HEADER = header/defines.h file_operation.h max.h
LIBS = -lm

all: $(PROGRAM).exe $(D_OUT) $(B)

$(PROGRAM).exe: $(OBJ)
	$(CC) $^ -o $@ $(LIBS)

$(B)%.o: %.c $(HEADER) $(B)
	$(CC) -c $< -o $@

$(B):
	mkdir $(B)

$(D_OUT):
	mkdir $(D_OUT)

clean:
	rm -f *.exe outputs/* build/*

vclean: # violent clean
	rm -rf *.exe outputs/ build/

test: $(TEST)
	./$^

.PHONY: clean test vclean
