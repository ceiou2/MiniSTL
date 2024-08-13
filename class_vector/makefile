CC = g++

CFLAGS = -g -lgtest -lpthread

all:testVector

testVector:testVector.cpp
	$(CC) -o $@ $^ $(CFLAGS)

.PHONY:clean

clean:
	rm testVector
