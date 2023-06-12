CC = clang++
CFLAGS = -std=c++11 -Wall -I /usr/local/Cellar/jsoncpp/1.9.5/include/
LDFLAGS = -lcurl -L /usr/local/Cellar/jsoncpp/1.9.5/lib -ljsoncpp

all: main

main: main.cpp userInfo.cpp alpacaStock.cpp algorithms.cpp
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

userInfo.o : userInfo.cpp
	$(CXX) $(CXXFLAGS) userInfo.cpp -o userInfo.o 

alpacaStock.o : alpacaStock.cpp
	$(CXX) $(CXXFLAGS) alpacaStock.cpp -o alpacaStock.o

algorithms.o : algorithms.cpp
	$(CXX) $(CXXFLAGS) algorithms.cpp -o algorithms.o
	
clean:
	rm -f main