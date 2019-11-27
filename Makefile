INCLUDE=-I. -I./gen-cpp -I./include -L./lib
gcc=g++
CPPFLAGS=--std=c++11 -O2 
LIB=-lthrift ./lib/libcrfpp.a

all: word_seg

thrift:
	@thrift --gen cpp word_seg.thrift 
	@rm -f gen-cpp/WordSegService_server.skeleton.cpp
	@thrift --gen py word_seg.thrift

word_seg: thrift
	$(gcc) *.cpp gen-cpp/*.cpp -o $@ $(INCLUDE) $(CPPFLAGS) $(LIB)

.PHONY: clean
clean:
	@rm -rf gen-cpp
	@rm -f word_seg
	@rm -rf gen-py
