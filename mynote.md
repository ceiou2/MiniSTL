## mynote

STL容器中可能会存在以其他容器为底层进行实现的情况
+ 如deque用vector的情况
或者algorithm用到functional的less greater的情况
但是为什么他们的实现没有包括到对应的头文件也能使用呢？
