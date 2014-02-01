MSG="String functionality test"
H_RULE="/*****************************************************************************/"
CC=g++
CC_FLAGS=-std=c++11
LIB=../SString.cpp

all: hello_print
	${CC} ${CC_FLAGS} ${LIB} api_test.cpp    -o api_test
	${CC} ${CC_FLAGS} ${LIB} append_test.cpp -o append_test

hello_print:
	@echo ${H_RULE}
	@echo ""
	@echo "      " ${MSG}
	@echo ""
	@echo ${H_RULE}

clean:
	rm api_test -f
	rm append_test -f
