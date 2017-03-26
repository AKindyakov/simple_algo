LIB=
FLAGS=-std=c++11 -Wall
CC=g++
#CC=clang++
PRODUCT=product

ut:
	@${CC} ${FLAGS} ${LIB} -o ${PRODUCT}/ut \


in:
	@${CC} ${FLAGS} ${LIB} -o ${PRODUCT}/test_app \
	simple_search_tree.cpp \
	test_app.cpp


clean:
	@rm -r -f ${PRODUCT}


prepare:
	@mkdir -p ${PRODUCT}

