PRODUCT=product

CC=g++
LIB=
FLAGS=-std=c++11 -Wall

test:
	${CC} ${FLAGS} ${LIB} -o ${PRODUCT}/test \
	reading.cpp \
	test.cpp \

ut:
	${CC} ${FLAGS} ${LIB} -o ${PRODUCT}/ut \
	ut.cpp

doc:
	latex -output-directory=${PRODUCT} -output-format=pdf doc.tex

clear:
	rm product -r

prepare:
	mkdir product

