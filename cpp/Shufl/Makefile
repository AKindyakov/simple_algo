LIB=
FLAGS=-std=c++11 -Wall
CC=g++
#CC=clang++
PRODUCT=product

ut: prepare
	${CC} ${FLAGS} ${LIB} -o ${PRODUCT}/ut \
	ut_test.cpp


in: prepare
	${CC} ${FLAGS} ${LIB} -o ${PRODUCT}/in \
	in_test.cpp


doc: prepare
	latex -output-directory=${PRODUCT} -output-format=pdf doc.tex


clean: prepare
	rm -r -f ${PRODUCT}


prepare:
	mkdir -p ${PRODUCT}

