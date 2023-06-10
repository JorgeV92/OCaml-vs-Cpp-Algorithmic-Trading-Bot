CC = clang++
CFLAGS = -std=c++11 -Wall -I /opt/homebrew/Cellar/jsoncpp/1.9.5/include/
LDFLAGS = -lcurl -L /opt/homebrew/Cellar/jsoncpp/1.9.5/lib -ljsoncpp

all: main test

main: main.cpp userInfo.cpp alpacaStock.cpp
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

userInfo.o : userInfo.cpp
	$(CC) $(CFLAGS) -c userInfo.cpp -o userInfo.o 

alpacaStock.o : alpacaStock.cpp
	$(CC) $(CFLAGS) -c alpacaStock.cpp -o alpacaStock.o 

test: test.cpp
	$(CC) $(CFLAGS) -o $@ $< $(LDFLAGS)
	
clean:
	rm -f main userInfo.o alpacaStock.o test
