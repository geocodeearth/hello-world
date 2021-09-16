GDAL_ROOT_DIR=$(shell brew --prefix gdal)

CXX=g++
CXXFLAGS=-std=c++17 -stdlib=libc++ -I ${GDAL_ROOT_DIR}/include
LDFLAGS=-L ${GDAL_ROOT_DIR}/lib
LDLIBS=-lgdal
OBJS=gdal_demo.cpp
BIN=gdal_demo

build: $(OBJS)
	$(CXX) $(LDLIBS) $(LDFLAGS) $(CXXFLAGS) -o ${BIN} $(OBJS)

run: build
	./${BIN}
