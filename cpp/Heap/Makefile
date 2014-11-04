LIB=
FLAGS=-std=c++0x -Wall
CC=g++-4.8
#CC=clang++
PRODUCT=product

ut:
	@${CC} ${FLAGS} ${LIB} -o ${PRODUCT}/heap_ut heap_ut.cpp

clean:
	@rm -r -f ${PRODUCT}

prepare:
	@mkdir -p ${PRODUCT}
