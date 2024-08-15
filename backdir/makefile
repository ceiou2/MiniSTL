CC=g++
CFLAGS=-g -lgtest -lpthread -I../Container_library

# 源文件
SRC=$(wildcard *.cpp)
# 目标可执行文件
TARGETS=$(SRC:.cpp=)

all:$(TARGETS)

# 通用规则
%:%.cpp
	$(CC) -o $@ $^ $(CFLAGS)

.PHONY:clean

clean:
	find . -type f -name "test*" ! -name "*.cpp" -delete
