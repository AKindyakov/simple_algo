MSG="String functionality test"
H_RULE="/*****************************************************************************/"
OUT_FILE=stringTest.out
CC=g++

all: hello_print
	${CC} ../SString.cpp test.cpp -std=c++11 -o ${OUT_FILE}

hello_print:
	@echo ${H_RULE}
	@echo ""
	@echo "      " ${MSG}
	@echo ""
	@echo ${H_RULE}

clean:
	rm ${OUT_FILE} -f
