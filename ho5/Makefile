CC=gcc
PROGRAM = ho5
OBJ = build/ho5.o build/max.o build/file_operation.o 
HEADER = defines.h file_operation.h max.h
LIBM = -lm
D_BUILD = build/

all: $(PROGRAM).exe

# $(PROGRAM): $(OBJ)
# 	$(CC) $^ -o $@ $(LIBM)
$(PROGRAM).exe: $(OBJ)
	$(CC) $^ -o $@ $(LIBM)

# %.o: %.c $(HEADER)
# 	$(CC) -c -g $^
$(D_BUILD)%.o: %.c $(HEADER)
	$(CC) -c $< -o $@

$(D_BUILD):
	mkdir $(D_BUILD)

clean:
	rm -f *.exe *.gch outputs/* build/*
  
run: $(PROGRAM).exe
	./$(PROGRAM).exe

.PHONY: clean run
