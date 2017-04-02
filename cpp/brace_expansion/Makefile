export CXXFLAGS := -std=c++14 -Wall
export CXX := g++ $(CXXFLAGS)
export PRODUCT := product

.PHONY: ut doc clean prepare


ut: prepare $(PRODUCT)/ut


clean:
	rm -r -f ${PRODUCT}


prepare:
	mkdir -p ${PRODUCT}


$(PRODUCT)/expansion.o: expansion.cpp expansion.h
	$(CXX) -c \
    -o $@ $<


$(PRODUCT)/expansion_ut.o: expansion_ut.cpp expansion.h
	$(CXX) -c \
    -o $@ $<


$(PRODUCT)/ut: $(PRODUCT)/expansion_ut.o $(PRODUCT)/expansion.o
	$(CXX) \
    -o $@ \
    $^
