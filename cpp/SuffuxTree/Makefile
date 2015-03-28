LIB=
FLAGS=-std=c++11 -Wall
CC=g++
#CC=clang++
PRODUCT=product

ut:
	${CC} ${FLAGS} ${LIB} -o ${PRODUCT}/ut \
	tree.cpp \
	ut_test.cpp

in:
	${CC} ${FLAGS} ${LIB} -o ${PRODUCT}/in \
	tree.cpp \
	in_test.cpp

doc:
	latex -output-directory=${PRODUCT} -output-format=pdf doc.tex

clear:
	rm product -r

prepare:
	mkdir product

