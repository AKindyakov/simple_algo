LIB=
FLAGS=-std=c++11 -Wall
CC=g++
#CC=clang++
PRODUCT=product

ut:
	${CC} ${FLAGS} ${LIB} -o ${PRODUCT}/ut \
	zfunction.cpp \
	ut_test.cpp


in:
	${CC} ${FLAGS} ${LIB} -o ${PRODUCT}/in \
	zfunction.cpp \
	in_test.cpp

hw:
	${CC} ${FLAGS} ${LIB} -o ${PRODUCT}/hw \
	hw.cpp

hw2:
	${CC} ${FLAGS} ${LIB} -o ${PRODUCT}/hw2 \
	hw2.cpp

doc:
	latex -output-directory=${PRODUCT} -output-format=pdf doc.tex

clean:
	rm -r -f ${PRODUCT}


prepare:
	mkdir -p ${PRODUCT}

