CC = g++
CFLAGS = -g -lgtest -lpthread

all:testString

testString:testString.cpp
	$(CC) -o $@ $^ $(CFLAGS)

.PHONY:clean

clean:
	rm testString
