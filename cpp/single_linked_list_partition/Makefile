LIB=
FLAGS=-std=c++11 -Wall
CC=g++
#CC=clang++
PRODUCT=product

single_linked_list_partition: prepare
	${CC} ${FLAGS} ${LIB} -o ${PRODUCT}/single_linked_list_partition \
	single_linked_list_partition.cpp

clean: prepare
	rm -r -f ${PRODUCT}


prepare:
	mkdir -p ${PRODUCT}

