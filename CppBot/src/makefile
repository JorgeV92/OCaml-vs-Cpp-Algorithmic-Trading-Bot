CC = clang++
CFLAGS = -std=c++11 -Wall -I /usr/local/Cellar/jsoncpp/1.9.5/include/ -I/usr/local/opt/openssl/include 
LDFLAGS = -lcurl -L /usr/local/Cellar/jsoncpp/1.9.5/lib -ljsoncpp -L/usr/local/opt/openssl/lib -lssl -lcrypto

all: main 

main: main.cpp userInfo.cpp alpacaStock.cpp algorithms.cpp
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)


userInfo.o : userInfo.cpp
	$(CC) $(CFLAGS) -c -o $@ userInfo.cpp

alpacaStock.o : alpacaStock.cpp
	$(CC) $(CFLAGS) -c -o $@ alpacaStock.cpp

algorithms.o : algorithms.cpp
	$(CC) $(CFLAGS) -c -o $@ algorithms.cpp

clean:
	rm -f main test *.o