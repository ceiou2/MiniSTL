CC=g++
CFLAGS=-g -lgtest -lpthread

all:testHashTable testUnorderedSet

testHashTable:testHashTable.cpp
	$(CC) -o $@ $^ $(CFLAGS)

testUnorderedSet:testUnorderedSet.cpp
	$(CC) -o $@ $^ $(CFLAGS)

.PHONY:clean

clean:
	rm testHashTable testUnorderedSet
