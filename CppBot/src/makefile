CC = g++
CFLAGS = -std=c++11 -Wall
LDFLAGS = -lcurl

all: main

main: main.cpp
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

clean:
	rm -f main