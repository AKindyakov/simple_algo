LIB=
FLAGS=-std=c++11 -Wall
CC=g++
#CC=clang++
PRODUCT=product

ut:
	${CC} ${FLAGS} ${LIB} -o ${PRODUCT}/ut \
	knuth_moris_pratt.cpp \
	ut_test.cpp

in: print_header
	${CC} ${FLAGS} ${LIB} -o ${PRODUCT}/in \
	knuth_moris_pratt.cpp \
	in_test.cpp

doc:
	latex -output-directory=${PRODUCT} -output-format=pdf doc.tex

clear:
	rm product -r

create_dir:
	mkdir product 

print_header:
	@echo "/********************************************************************/"
	@echo " -------------------------------------------------------------------- "
	@echo " -------------------------------------------------------------------- "
	@echo " -------------------------------------------------------------------- "
	@echo "/********************************************************************/"
