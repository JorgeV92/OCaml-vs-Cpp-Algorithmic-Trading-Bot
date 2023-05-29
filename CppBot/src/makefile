CC = g++
CFLAGS = -std=c++11 -Wall
LDFLAGS = -lcurl

all: main

main: main.cpp userInfo.cpp alpacaStock.cpp
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

userInfo.o : userInfo.cpp
	$(CXX) $(CXXFLAGS) userInfo.cpp -o userInfo.o 

alpacaStock.o : alpacaStock.cpp
	$(CXX) $(CXXFLAGS) alpacaStock.cpp -o alpacaStock.o 
	
clean:
	rm -f main