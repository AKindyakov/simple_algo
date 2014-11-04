LIB=
FLAGS=-std=c++0x -Wall
#CC=g++-4.8
CC=clang++
PRODUCT=product

ut:
	@${CC} ${FLAGS} ${LIB} -o ${PRODUCT}/ut \
merge_sort.cpp \
insertion_sort.cpp \
selection_sort.cpp \
ut_test.cpp

	@${CC} ${FLAGS} ${LIB} -o ${PRODUCT}/heap_ut heap_ut.cpp

in:
	@${CC} ${FLAGS} ${LIB} -o ${PRODUCT}/in \
merge_sort.cpp \
insertion_sort.cpp \
selection_sort.cpp \
input_test.cpp

ext_sort_app:
	@${CC} ${FLAGS} ${LIB} -o ${PRODUCT}/ext_sort_app \
external_sort_app.cpp \
external_sort.cpp \
merge_sort.cpp \
insertion_sort.cpp

clean:
	@rm -r -f ${PRODUCT}

prepare:
	@mkdir -p ${PRODUCT}
