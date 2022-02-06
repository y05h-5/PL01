CC = gcc
PROGRAM = ex6
D_OUT = outputs/
B = build/
H = header/
TEST = test.sh
OBJ = $(B)main.o $(B)flight.o $(B)file_handler.o $(B)error_handler.o 
HEADER = $(H)header/defines.h $(H)header/flight.h $(H)header/file_handler.h $(H)header/error_handler.h
LIBS = -lm

all: $(PROGRAM).exe $(D_OUT) $(B)

$(PROGRAM).exe: $(OBJ)
	$(CC) $^ -o $@ $(LIBS)

$(B)%.o: %.c #$(HEADER) $(B)
	$(CC) -c $< -o $@

$(B):
	mkdir $(B)

$(D_OUT):
	mkdir $(D_OUT)

clean:
	rm -f *.exe outputs/* build/* result.txt

vclean: # violent clean
	rm -rf *.exe outputs/ build/ result.txt

test: $(TEST)
	./$^

.PHONY: clean test vclean
