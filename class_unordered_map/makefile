CC=g++
CFLAGS=-g -lgtest -lpthread

all:testHashTable testUnorderedMap

testHashTable:testHashTable.cpp
	$(CC) -o $@ $^ $(CFLAGS)

testUnorderedMap:testUnorderedMap.cpp
	$(CC) -o $@ $^ $(CFLAGS)

.PHONY:clean

clean:
	rm testHashTable testUnorderedMap
