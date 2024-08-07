CC=g++
CFLAGS=-g -lgtest -lpthread

all:testHashTable

testHashTable:testHashTable.cpp
	$(CC) -o $@ $^ $(CFLAGS)

.PHONY:clean

clean:
	rm testHashTable
