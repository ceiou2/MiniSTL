## MiniDeque 详细设计报告

### 1.需求分析
#### 1.1.数据结构
+ 实现双端队列，提供在两端插入和删除的能力，同时支持随机访问。
#### 1.2.性能
+ 
#### 1.3.异常安全
+ 确保所有操作都是异常安全的。
#### 1.4.内存管理
+ 合理管理内存，避免内存泄漏。

### 2.设计目标
+ 实现一个类似STL中deque的双向链表，提供基本的操作接口，实现部分C++11标准后定义的函数。
+ 确保操作的效率和异常安全性。
+ 合理管理内存，提供良好的性能和资源利用率。

### 3.数据结构设计
#### 1.deque类
##### 1.1.数据存储
+ 采用map数组+缓冲区buffer的形式进行数据的存储。
+ map数组：使用MiniVector作为map数组的容器，其中的节点存放每一个指向buffer的指针。
+ buffer： 固定大小数组用以存放数据。

##### 1.2.迭代器
###### 1.2.1.iterator：
+ 数据成员：
T* cur:指向当前正在遍历的元素。  
T* first:指向当前buffer的首地址。  
T* last:指向当前buffer的末尾的下一个位置。(不一定是容量末尾，可能是长度末尾)  
map_pointer node:指向map中指向当前buffer的map节点。  

##### 1.3.成员变量
+ iterator start:储存头buffer的信息，其中cur指向首元素。
+ iterator finish:储存尾buffer的信息，其中cur指向尾元素的下一个位置。

### 4.接口设计
+ 构造函数
+ 添加元素：提供在头部和尾部添加元素的方法。
+ 删除元素：提供删除指定元素的方法。
+ 获取长度：提供获取deque的方法。

### 5.实现细节
+ 内存管理：使用智能指针来管理链表中的节点，确保在异常情况下不会导致内存泄漏。
+ 异常安全：所有操作中使用RAII技术，确保在异常情况下能够正确释放资源。

### 6.测试计划
+ 编写单元测试，测试每个public成员方法。