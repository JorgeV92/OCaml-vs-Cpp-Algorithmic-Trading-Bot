CC = g++
CFLAGS = -std=c++11 -Wall
LDFLAGS = -lcurl

all: main

main: main.cpp userInfo.cpp
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

userInfo.o : userInfo.cpp
	$(CXX) $(CXXFLAGS) userInfo.cpp -o userInfo.o 
	
clean:
	rm -f main