CC=gcc
CFLAGS = -lm
OBJ= errors.o linearsystem.o utils.o getio.o main.o
test: clean all
	./pdeSolver -i 300 -nx 100 -ny 200 -o out.dat; if ls *.o > /dev/null 2>&1; then rm *.o; fi
all: $(OBJ) #compila, produz um executável chamado pdeSolver
	$(CC) -o pdeSolver $^ $(CFLAGS)
clean: #remove temporários e outros do makefile
	if ls *.o > /dev/null 2>&1; then rm *.o; fi
doc: #gera documentação doxygen em html
	doxygen doxyfile
%.o: %.c %.h
	$(CC) -c -o $@ $< $(CFLAGS)
