LIB=
FLAGS=-std=c++11 -Wall -g
CC=g++
#CC=clang++
PRODUCT=product

t:
	${CC} ${FLAGS} ${LIB} -o ${PRODUCT}/test \
	test.cpp

ut:
	${CC} ${FLAGS} ${LIB} -o ${PRODUCT}/ut \
	tree.cpp \
	fuzzy_search.cpp \
	ut_test.cpp

hw:
	${CC} ${FLAGS} ${LIB} -o ${PRODUCT}/hw \
	hw.cpp

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

