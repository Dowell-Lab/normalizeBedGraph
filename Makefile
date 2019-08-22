CXX=clang++
CXXFLAGS=-Wall -Werror -march=native -O2 -flto --std=c++11

default: normalizeBedGraph

normalizeBedGraph: normalizeBedGraph.o
	$(CXX) $(CXXFLAGS) normalizeBedGraph.o -o normalizeBedGraph

build: normalizeBedGraph.o
	$(CXX) $(CXXFLAGS) -c normalizeBedGraph.cpp -o normalizeBedGraph.o

clean:
	rm -f normalizeBedGraph.o
	rm -f normalizeBedGraph
