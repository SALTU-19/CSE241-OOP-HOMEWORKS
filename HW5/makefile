Test: test 
test: main.cpp AbstractHex.cpp AbstractHex.h cell.cpp cell.h HexVector.cpp HexVector.h HexArray1D.h HexArray1D.cpp HexAdapter.h HexAdapter.cpp error.h
	g++ -std=c++11 -c main.cpp
	g++ -std=c++11 -c AbstractHex.cpp 
	g++ -std=c++11 -c HexVector.cpp 
	g++ -std=c++11 -c HexArray1D.cpp 
	g++ -std=c++11 -c HexAdapter.cpp 
	g++ -std=c++11 -c cell.cpp 
	g++ -std=c++11 -o main main.o AbstractHex.o HexVector.o HexArray1D.o HexAdapter.o cell.o
	./main