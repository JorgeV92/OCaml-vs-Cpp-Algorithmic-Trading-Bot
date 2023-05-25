CC = g++
CFLAGS = -std=c++11 -Wall
LDFLAGS = -lcurl

all: main

main: main.cpp userInfo.cpp alpaca.cpp
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

userInfo.o : userInfo.cpp
	$(CXX) $(CXXFLAGS) userInfo.cpp -o userInfo.o 

alpaca.o : alpaca.cpp
	$(CXX) $(CXXFLAGS) alpaca.cpp -o alpaca.o 
	
clean:
	rm -f main