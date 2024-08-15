CC=g++
CFLAGS=-g -lgtest -lpthread

SRC=$(wildcard *.cpp)
TARGET=$(SRC:.cpp=)

all:$(TARGET)

%:%.cpp
	$(CC) -o $@ $^ $(CFLAGS)

.PHONY:clean

clean:
	find . -type f -executable -delete
