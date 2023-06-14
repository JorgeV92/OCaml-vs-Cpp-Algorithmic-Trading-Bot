CC = clang++
CFLAGS = -std=c++11 -Wall -I /usr/local/Cellar/jsoncpp/1.9.5/include/ -I /usr/local/include/catch2
LDFLAGS = -lcurl -L /usr/local/Cellar/jsoncpp/1.9.5/lib -ljsoncpp

all: main test

main: main.cpp userInfo.cpp alpacaStock.cpp algorithms.cpp
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

test: test.cc
	$(CC) $(CFLAGS) -o $@ test.cc

userInfo.o : userInfo.cpp
	$(CC) $(CFLAGS) -c -o $@ userInfo.cpp

alpacaStock.o : alpacaStock.cpp
	$(CC) $(CFLAGS) -c -o $@ alpacaStock.cpp

algorithms.o : algorithms.cpp
	$(CC) $(CFLAGS) -c -o $@ algorithms.cpp

clean:
	rm -f main test *.o