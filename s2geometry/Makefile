S2_ROOT_DIR=$(shell brew --prefix s2geometry)

CXX=g++
CXXFLAGS=-std=c++17 -stdlib=libc++ -I ${S2_ROOT_DIR}/include
LDFLAGS=-L ${S2_ROOT_DIR}/lib
LDLIBS=-ls2
OBJS=s2_demo.cpp
BIN=s2_demo

build: $(OBJS)
	$(CXX) $(LDLIBS) $(LDFLAGS) $(CXXFLAGS) -o ${BIN} $(OBJS)

run: build
	./${BIN}
