all: #compila, produz um executável chamado pdeSolver
clean: #remove temporários e outros do makefile
	# rm -rf doxygen_docs/
	rm *.o *.out
doc: #gera documentação doxygen em html
	doxygen doxyfile
