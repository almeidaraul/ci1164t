CC=gcc
CFLAGS = -lm
OBJ= errors.o linearsystem.o utils.o getio.o main.o
test: clean all
	./pdeSolver -i 30 -nx 4 -ny 5 -o saida.txt; if ls *.o > /dev/null 2>&1; then rm *.o; fi
all: $(OBJ) #compila, produz um executável chamado pdeSolver
	$(CC) -o pdeSolver $^ $(CFLAGS)
clean: #remove temporários e outros do makefile
	if ls *.o > /dev/null 2>&1; then rm *.o; fi
doc: #gera documentação doxygen em html
	doxygen doxyfile
%.o: %.c %.h
	$(CC) -c -o $@ $< $(CFLAGS)
