LIB=
FLAGS=-std=c++0x -Wall
CC=g++-4.8
PRODUCT=product

ut:
	@${CC} ${FLAGS} ${LIB} -o ${PRODUCT}/ut \
merge_sort.cpp \
insertion_sort.cpp \
selection_sort.cpp \
ut_test.cpp

in:
	@${CC} ${FLAGS} ${LIB} -o ${PRODUCT}/in \
merge_sort.cpp \
insertion_sort.cpp \
selection_sort.cpp \
input_test.cpp

debug:
	FLAGS=${FLAGS} -g
	cc

clean:
	@rm -r -f ${PRODUCT}

prepare:
	@mkdir -p ${PRODUCT}
