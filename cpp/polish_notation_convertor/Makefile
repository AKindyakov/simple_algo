LIB=
FLAGS=-std=c++11 -Wall
CC=g++
#CC=clang++
PRODUCT=product

test: prepare
	${CC} ${FLAGS} ${LIB} -o ${PRODUCT}/test \
	convertor.cpp \
	test.cpp

clean: prepare
	rm -r -f ${PRODUCT}

prepare:
	mkdir -p ${PRODUCT}

