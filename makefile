CC=gcc
CFLAGS = -lm
OBJ= errors.o linearsystem.o utils.o getio.o main.o
all: $(OBJ) #compila, produz um executável chamado pdeSolver
	$(CC) -o pdeSolver $^ $(CFLAGS)
clean: #remove temporários e outros do makefile
	rm *.o *.out
doc: #gera documentação doxygen em html
	doxygen doxyfile
# fazer uma makefile bonita depois
%.o: %.c %.h
	$(CC) -c -o $@ $< $(CFLAGS)
