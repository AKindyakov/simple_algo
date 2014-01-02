
all: clean prepare
	g++ quicksort.cpp test.cpp -o product/solve 

debug: clean prepare
	g++ quicksort.cpp test.cpp -o product/solve -g

clean:
	rm -r -f product

prepare:
	mkdir product
	
